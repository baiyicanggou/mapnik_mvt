#ifndef MAKE_VECTOR_TILE_HPP
#define MAKE_VECTOR_TILE_HPP

#include <memory>

#include "filter_table.hh"
#include "mapnik_tile.hh"

namespace mapnik {
class Map;
}

namespace flywave {
namespace nik {

bool make_vector_tile(
    mapnik_tile &tile, mapnik::Map &map, int buffer_size, unsigned tile_size,
    std::shared_ptr<const filter_table> filter_table = nullptr);
}
} // namespace flywave
#endif
