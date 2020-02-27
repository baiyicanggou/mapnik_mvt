#include "mvt_tile.hh"

#include <vector_tile_compression.hpp>
#include <vector_tile_tile.hpp>

namespace flywave {
namespace nik {

mvt_tile::~mvt_tile() {
}

std::string mvt_tile::get_data(int compression_level) const {
  auto &message = _mvt_tile->get_buffer();
  if (compression_level != 0) {
    int strategy = Z_DEFAULT_STRATEGY;
    int level = Z_DEFAULT_COMPRESSION;
    std::string compressed_data;
    mapnik::vector_tile_impl::zlib_compress(message, compressed_data, false,
                                            compression_level, strategy);
    return compressed_data;
  }
  return "";
}

void mvt_tile::from_mvt(mapnik::vector_tile_impl::tile &&str) {
  _mvt_tile=std::make_unique<mapnik::vector_tile_impl::tile>(std::move(str));
}

mapnik::vector_tile_impl::tile const &mvt_tile::vtile() const {
  return *_mvt_tile;
}

mapnik::vector_tile_impl::tile &mvt_tile::vtile() { return *_mvt_tile; }
} // namespace nik
} // namespace flywave
