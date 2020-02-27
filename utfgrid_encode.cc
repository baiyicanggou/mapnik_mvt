#include "utfgrid_encode.hh"

#include <unordered_map>

#include <mapnik/unicode.hpp>

namespace flywave {
namespace nik {

struct value_to_json_visitor {
  js_value operator()(const mapnik::value_null &val) { return js_value(); }

  js_value operator()(const mapnik::value_bool &val) { return js_value(val); }

  js_value operator()(const mapnik::value_integer &val) {
    return js_value(static_cast<uint>(val));
  }

  js_value operator()(const mapnik::value_double &val) { return js_value(val); }

  js_value operator()(const mapnik::value_unicode_string &val) {
    std::string utf8_str;
    mapnik::to_utf8(val, utf8_str);
    return js_value(utf8_str.c_str(), utf8_str.size());
  }
};

std::string encode_utfgrid(const mapnik::grid_view &utfgrid, unsigned size) {
  js_document root(rapidjson::kObjectType);
  js_value jgrid(rapidjson::kArrayType);

  using lookup_type = mapnik::grid::lookup_type;
  using value_type = mapnik::grid::value_type;
  using feature_type = mapnik::grid::feature_type;
  using keys_type = std::unordered_map<lookup_type, value_type>;

  std::vector<lookup_type> key_order;
  keys_type keys;

  const mapnik::grid::feature_key_type &feature_keys =
      utfgrid.get_feature_keys();

  std::uint16_t codepoint = 32;
  for (unsigned y = 0; y < utfgrid.height(); y += size) {
    std::string line;
    const value_type *row = utfgrid.get_row(y);
    for (unsigned x = 0; x < utfgrid.width(); x += size) {
      value_type feature_id = row[x];
      auto feature_itr = feature_keys.find(feature_id);
      lookup_type val;
      if (feature_itr == feature_keys.end()) {
        feature_id = mapnik::grid::base_mask;
      } else {
        val = feature_itr->second;
      }
      auto key_iter = keys.find(val);
      if (key_iter == keys.end()) {
        if (codepoint == 34)
          ++codepoint;
        else if (codepoint == 92)
          ++codepoint;
        if (feature_id == mapnik::grid::base_mask) {
          keys[""] = codepoint;
          key_order.push_back("");
        } else {
          keys[val] = codepoint;
          key_order.push_back(val);
        }
        line.append(reinterpret_cast<char *>(&codepoint), sizeof(codepoint));
        ++codepoint;
      } else {
        line.append(reinterpret_cast<char *>(&key_iter->second),
                    sizeof(key_iter->second));
      }
    }
    jgrid.PushBack(js_value(line.c_str(), line.size()), root.GetAllocator());
  }
  std::string g_str = "grid";
  root.AddMember(js_value(g_str.c_str(), g_str.size()), jgrid,
                 root.GetAllocator());

  js_value jkeys(rapidjson::kArrayType);
  for (const auto &key_id : key_order) {
    jkeys.PushBack(js_value(key_id.c_str(), key_id.size()),
                   root.GetAllocator());
  }
  std::string k_str = "keys";
  root.AddMember(js_value(k_str.c_str(), k_str.size()), jkeys,
                 root.GetAllocator());

  js_value jdata(rapidjson::kObjectType);
  std::string d_str = "data";
  root.AddMember(js_value(d_str.c_str(), d_str.size()), jdata,
                 root.GetAllocator());

  const feature_type &g_features = utfgrid.get_grid_features();
  const std::set<std::string> &attributes = utfgrid.get_fields();
  feature_type::const_iterator feat_end = g_features.end();
  for (const std::string &key_item : key_order) {
    if (key_item.empty()) {
      continue;
    }

    feature_type::const_iterator feat_itr = g_features.find(key_item);
    if (feat_itr == feat_end) {
      continue;
    }

    bool found = false;
    js_value jfeature(rapidjson::kObjectType);
    mapnik::feature_ptr feature = feat_itr->second;
    for (const std::string &attr : attributes) {
      value_to_json_visitor val_to_json;
      if (attr == "__id__") {
        jfeature.AddMember(
            js_value{attr.c_str(), static_cast<unsigned>(attr.size())},
            js_value{static_cast<unsigned>(feature->id())},
            root.GetAllocator());
      } else if (feature->has_key(attr)) {
        found = true;
        jfeature.AddMember(
            js_value{attr.c_str(), static_cast<unsigned>(attr.size())},
            js_value{
                mapnik::util::apply_visitor(val_to_json, feature->get(attr))},
            root.GetAllocator());
      }
    }

    if (found) {
      auto c_str = feat_itr->first.c_str();
      root.AddMember(js_value(c_str, strlen(c_str)), jfeature,
                     root.GetAllocator());
    }
  }

  return to_json(root);
}
} // namespace nik
} // namespace flywave
