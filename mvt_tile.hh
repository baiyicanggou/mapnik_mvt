#pragma once

#include "mapnik_tile.hh"

#include <vector_tile_datasource_pbf.hpp>
#include <vector_tile_tile.hpp>

#include <mapnik/image_scaling.hpp>
#include <mapnik/map.hpp>

namespace mapnik {
namespace vector_tile_impl {
struct tile;
}
} // namespace mapnik

namespace flywave {
namespace nik {

class mvt_tile : public mapnik_tile {
public:
  mvt_tile(const tile_ext_id &coord) : mapnik_tile(coord), _mvt_tile(nullptr) {}

  mvt_tile(const mvt_tile &) = default;
  mvt_tile &operator=(const mvt_tile &) = default;

  mvt_tile(mvt_tile &&o) = default;
    
  mvt_tile &operator=(mvt_tile &&o)= default;

  virtual ~mvt_tile();

  friend class mvt_tiler;

  std::string get_data(int compression_level = 0) const;

  void from_mvt(mapnik::vector_tile_impl::tile &&str);

  mapnik::vector_tile_impl::tile const &vtile() const;
  mapnik::vector_tile_impl::tile &vtile();

private:
  std::unique_ptr<mapnik::vector_tile_impl::tile> _mvt_tile;
};

class mvt_gzip_tile : public mapnik_tile {
public:
  explicit mvt_gzip_tile(const mvt_tile &t)
      : tile_(t), compression_level_(-1) {}

  mvt_gzip_tile(const mvt_tile &t, int compression_level)
      : tile_(t), compression_level_(compression_level) {}

  std::string get_data(int compression_level) {
    return tile_.get_data(compression_level);
  }

private:
  const mvt_tile &tile_;
  int compression_level_;
};

} // namespace nik
} // namespace flywave
