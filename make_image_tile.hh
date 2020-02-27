#ifndef MAKE_IMAGE_TILE_HPP
#define MAKE_IMAGE_TILE_HPP

#include "util.hh"

namespace mapnik {
class Map;
}

namespace flywave {
namespace nik {

bool make_image_tile(mapnik_tile &tile, mapnik::Map &map, int buffer_size,
                     int tile_size);
}
} // namespace flywave
#endif
