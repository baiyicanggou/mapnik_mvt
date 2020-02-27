#include "geometry_featureset.hh"

#include <mapnik/geometry.hpp>

#include <mapnik/datasource.hpp>
#include <mapnik/feature.hpp>
#include <mapnik/feature_factory.hpp>
#include <mapnik/geometry.hpp>

#pragma GCC diagnostic push
#include <boost/range/adaptor/reversed.hpp>
#include <mapnik/warning_ignore.hpp>
#pragma GCC diagnostic pop

#include <boost/lexical_cast.hpp>

namespace flywave {
namespace nik {

struct field_value_helper {
  mapnik::feature_ptr feature;
  std::string key;

  void operator()(value const &geom, const char *k, mapnik::feature_ptr fe) {
    feature = fe;
    key = k;
    return apply_visitor(*this, geom);
  }

  void operator()(null_value_t const &) {
    feature->put_new(key, mapnik::value_null{});
  }

  void operator()(bool const &v) { feature->put(key, mapnik::value_bool{v}); }

  void operator()(uint64_t const &i) {
    feature->put_new(key, mapnik::value_integer(i));
  }

  void operator()(int64_t const &i) {
    feature->put_new(key, mapnik::value_integer(i));
  }

  void operator()(double const &d) {
    feature->put_new(key, mapnik::value_double{d});
  }

  void operator()(std::string const &s) {
    feature->put_new(key, mapnik::value_unicode_string{
                              s.c_str(), static_cast<int32_t>(s.size())});
  }

  template <typename T> void operator()(T const &v) {}
};

void setup_properties(const property_map &map, mapnik::feature_ptr fe) {
  for (auto &pr : map) {
    field_value_helper{}(pr.second, pr.first.c_str(), fe);
  }
}

mapnik::feature_ptr make_feature(mapnik::context_ptr ctx,
                                 unsigned int feature_id,
                                 const nik::feature<double> &feat) {
  mapnik::feature_ptr feature(mapnik::feature_factory::create(ctx, feature_id));

  feature->set_geometry(mapnik::geometry::geometry<double>(feat.geometry));

  if (feat.id) {
    auto iden = feat.id.value();
    if (iden.type() == typeid(uint64_t)) {
      feature->set_id(
          static_cast<mapnik::value_integer>(boost::get<uint64_t>(iden)));
    } else if (iden.type() == typeid(int64_t)) {
      feature->set_id(
          static_cast<mapnik::value_integer>(boost::get<int64_t>(iden)));
    } else if (iden.type() == typeid(double)) {
      feature->set_id(
          static_cast<mapnik::value_integer>(boost::get<double>(iden)));
    } else if (iden.type() == typeid(std::string)) {
      feature->set_id(static_cast<mapnik::value_integer>(
          boost::lexical_cast<int32_t>(boost::get<std::string>(iden))));
    }
  }

  setup_properties(feat.properties, feature);
  return feature;
}

geometry_featureset::geometry_featureset(mapnik::box2d<double> const &box,
                                         const feature_collection<double> &fs,
                                         array_type &&index_array)
    : ctx_(std::make_shared<mapnik::context_type>()), fs_(fs), box_(box),
      index_array_(std::move(index_array)), index_itr_(index_array_.begin()),
      index_end_(index_array_.end()), feature_id_(1) {}

mapnik::feature_ptr geometry_featureset::next() {
  if (index_itr_ != index_end_) {
    auto &item = *index_itr_++;
    std::size_t index = item.second;
    if (index < fs_.size()) {
      mapnik::feature_ptr feature = make_feature(ctx_, feature_id_, fs_[index]);
      feature_id_++;
      return feature;
    }
  }

  return mapnik::feature_ptr();
}

} // namespace nik
} // namespace flywave
