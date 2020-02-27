#ifndef MAKE_UTFGIRD_TILE_HPP
#define MAKE_UTFGIRD_TILE_HPP

#include "mapnik_tile.hh"
#include "util.hh"
namespace mapnik {
class Map;
}

namespace flywave {
namespace nik {

bool make_utfgrid_tile(mapnik_tile &tile, mapnik::Map &map,
                       std::string const &key, int buffer_size);
}
} // namespace flywave

#endif
