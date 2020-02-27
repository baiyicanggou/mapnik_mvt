#include "mapnik_source.hh"
#include "mapnik_tile.hh"

#include "cached_datasource.hh"
#include "make_geometry_datasource.hh"
#include "make_image_tile.hh"
#include "util.hh"
#include "virtual_datasource.hh"

#include <mapnik/agg_renderer.hpp>
#include <mapnik/config.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/rule.hpp>

namespace flywave {
namespace nik {

void mapnik_source::init(map_options &options) noexcept {
  for (auto &mo : options) {
    auto info = load_map(mo);
    _maps.emplace(mo.name, info);
  }
}

std::shared_ptr<map_data> mapnik_source::load_map(const map_option &mp) {
  auto map_data_ = std::make_shared<map_data>(mp.map);
  nik::calculate_layers_sd(map_data_->map);
  for (mapnik::layer &layer : map_data_->map.layers()) {
    std::string name = layer.name();
    layer_info linfo;
    linfo.name = name;
    map_data_->layer_info_map.emplace(std::move(name), std::move(linfo));
  }
  return map_data_;
}

void mapnik_source::active_layer(const std::string &style,
                                 std::set<std::string> *layers) {
  auto map_data_itr = _maps.find(style);
  map_data &minfo = *map_data_itr->second;
  if (map_data_itr == _maps.end()) {
    return;
  }

  if (layers == nullptr) {
    for (auto &layer : minfo.map.layers()) {
      auto ds_map_iter = _datasources.find(layer.name());
      if (ds_map_iter != _datasources.end()) {
        layer.set_datasource(ds_map_iter->second);
        layer.set_active(true);
      } else {
        layer.set_active(false);
      }
    }
  } else {
    const auto &requested_layers = *layers;
    for (auto &layer : minfo.map.layers()) {
      bool requested =
          (requested_layers.find(layer.name()) != requested_layers.end());
      auto ds_map_iter = _datasources.find(layer.name());
      if (ds_map_iter != _datasources.end()) {
        layer.set_datasource(ds_map_iter->second);
        layer.set_active(requested);
      } else {
        layer.set_active(requested);
      }
    }
  }
}

} // namespace nik
} // namespace flywave
