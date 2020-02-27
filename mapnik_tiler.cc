#include "mapnik_tiler.hh"
#include "mapnik_tile.hh"

#include "make_image_tile.hh"

#include <mapnik/agg_renderer.hpp>
#include <mapnik/config.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/grid/grid_renderer.hpp>
#include <mapnik/grid/grid_view.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/rule.hpp>

namespace flywave {
namespace nik {

std::unique_ptr<nik::mapnik_tile>
mapnik_tiler::create_mapnik_tile(const nik::tile_ext_id &coord) const {
  source()->active_layer(options()->style_name, options()->layers.get());

  mapnik::Map &map = source()->map(options()->style_name);
  auto metatile = std::make_unique<mapnik_ext_tile>(grid(), coord);
  try {
    render(*metatile, map);
  } catch (const std::exception &e) {
    return std::unique_ptr<nik::mapnik_tile>();
  }
  return std::move(metatile);
}

void mapnik_tiler::render(mapnik_ext_tile &etile, mapnik::Map &map) const {
  nik::make_image_tile(etile, map, 256, 256);
}
} // namespace nik
} // namespace flywave
