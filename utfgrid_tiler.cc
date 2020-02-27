#include "utfgrid_tiler.hh"
#include "make_utfgrid_tile.hh"

namespace flywave {
namespace nik {

void utfgrid_tiler::render(mapnik_ext_tile &etile, mapnik::Map &map) const {
  nik::make_utfgrid_tile(etile, map, options()->utfgrid_key, 256);
}

} // namespace nik
} // namespace flywave
