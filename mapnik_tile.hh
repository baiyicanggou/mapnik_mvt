#pragma once

#include "grid.hh"
#include "tile.hh"

#include <mapnik/map.hpp>

namespace flywave {
namespace nik {

class mapnik_ext_tile : public nik::mapnik_tile {
public:
  mapnik_ext_tile(const grid *g) : grid_(g) {}

  mapnik_ext_tile(const nik::tile_ext_id &_id) : mapnik_tile(_id) {}

  mapnik_ext_tile(const grid *g, const nik::tile_ext_id &_id)
      : mapnik_tile(_id), grid_(g) {}

  mapnik::box2d<double> get_bbox();

  const nik::tile_ext_id &eid() { return id; }

  virtual ~mapnik_ext_tile();

  const grid *grid_;
};
} // namespace nik
} // namespace flywave
