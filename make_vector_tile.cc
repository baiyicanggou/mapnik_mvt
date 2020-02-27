#include "make_vector_tile.hh"

#include "subtiler.hh"
#include "tile.hh"

#include <mapnik/feature.hpp>
#include <mapnik/map.hpp>

#include <vector_tile_processor.hpp>
#include <vector_tile_projection.hpp>

namespace flywave {
namespace nik {

static void split_to_mvt_tiles(subtiler &stiler, mapnik_tile &metatile,
                               size_t width, size_t height, size_t buf_size) {
  const tile_ext_id &metatile_id = metatile.id;
  size_t tile_image_width = width / metatile_id.width();
  size_t tile_image_height = height / metatile_id.height();
  size_t tile_i = 0;
  unsigned int z = metatile_id.id().z;
  for (unsigned y = 0; y < width; y += tile_image_height) {
    for (unsigned x = 0; x < height; x += tile_image_width) {
      tile_id coord{x, y, z};
      auto &t = metatile.tiles[tile_i++];
      std::string &tile_data = t.data;
      try {
        tile_data = stiler.make_subtiler(coord, 4096, buf_size);
      } catch (...) {
        throw std::current_exception();
      }
    }
  }
}

bool make_vector_tile(mapnik_tile &tile, mapnik::Map &map, int buffer_size,
                      unsigned tile_size,
                      std::shared_ptr<const filter_table> filter_table) {
  typedef mapnik::vector_tile_impl::processor renderer_type;
  auto metatile_bbox = tile.id.get_bbox();
  map.zoom_to_box(metatile_bbox);

  renderer_type ren(map);
  mapnik::vector_tile_impl::tile out_tile(metatile_bbox, tile_size,
                                          buffer_size);
  ren.set_simplify_distance(5.0);
  ren.update_tile(out_tile);
  bool ret = out_tile.is_painted();
  mvt_tile vtile(tile.id);
  vtile.from_mvt(std::move(out_tile));
  subtiler stiler(vtile.get_data(), tile.id, filter_table);
  mapnik_ext_tile metatile(tile.id);
  try {
    split_to_mvt_tiles(stiler, metatile, tile_size, tile_size, buffer_size);
  } catch (...) {
    return false;
  }
  tile = std::move(metatile);
  return ret;
}

} // namespace nik
} // namespace flywave
