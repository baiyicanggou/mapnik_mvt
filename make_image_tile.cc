#include "make_image_tile.hh"

#include <mapnik/agg_renderer.hpp>
#include <mapnik/request.hpp>

namespace flywave {
namespace nik {

bool make_image_tile(mapnik_tile &tile, mapnik::Map &map, int buffer_size,
                     int tile_size) {
  auto metatile_bbox = tile.id.get_bbox();
  const int map_width = tile_size * tile.id.width();
  const int map_height = tile_size * tile.id.height();

  map.resize(map_width, map_height);
  map.zoom_to_box(metatile_bbox);

  mapnik::request metatile_req(tile_size, tile_size, metatile_bbox);
  metatile_req.set_buffer_size(buffer_size);
  mapnik::box2d<double> metatile_buf_bbox = metatile_req.get_buffered_extent();

  mapnik_tile metatile(tile.id);
  try {
    mapnik::image_rgba8 image(map_width, map_height);
    mapnik::agg_renderer<mapnik::image_rgba8> ren(map, image, 1);
    ren.apply();
    split_to_tiles(image, metatile);
  } catch (const std::exception &e) {
    return false;
  }
  tile = std::move(metatile);
  return true;
}
} // namespace nik
} // namespace flywave
