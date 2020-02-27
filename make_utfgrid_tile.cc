
#include "make_utfgrid_tile.hh"
#include <mapnik/grid/grid.hpp>
#include <mapnik/grid/grid_renderer.hpp>
#include <mapnik/request.hpp>

namespace flywave {
namespace nik {

bool make_utfgrid_tile(mapnik_tile &tile, mapnik::Map &map,
                       std::string const &key, int buffer_size) {
  mapnik::box2d<double> metatile_bbox = tile.id.get_bbox();
  const int map_width = 256 * tile.id.width();
  const int map_height = 256 * tile.id.height();

  map.resize(map_width, map_height);
  map.zoom_to_box(metatile_bbox);

  mapnik::request metatile_req(256, 256, metatile_bbox);
  metatile_req.set_buffer_size(buffer_size);
  mapnik::box2d<double> metatile_buf_bbox = metatile_req.get_buffered_extent();

  mapnik_tile metatile(tile.id);
  try {
    mapnik::grid utf_grid(map_width, map_height, key);
    mapnik::grid_renderer<mapnik::grid> ren(map, utf_grid, 1);
    ren.apply();
    split_to_tiles(utf_grid, metatile);
  } catch (const std::exception &e) {
    return false;
  }
  tile = std::move(metatile);
  return true;
}
} // namespace nik
} // namespace flywave
