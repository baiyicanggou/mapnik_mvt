#include "mvt_tiler.hh"
#include "make_vector_tile.hh"

namespace flywave {
namespace nik {

void mvt_tiler::render(mapnik_ext_tile &etile, mapnik::Map &map) const {
  mvt_tiler_options *opts = this->options();
  make_vector_tile(etile, map, 256, grid()->tile_size(), opts->filter_table);
}

} // namespace nik
} // namespace flywave
