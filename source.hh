#pragma once

#include <functional>
#include <stdint.h>

#include "tile.hh"
#include "util.hh"

namespace flywave {
namespace nik {

class source {
public:
  source() {}

  source(source &&other) = default;
  source &operator=(source &&other) = default;

  virtual ~source() = default;

  const tile_bounds &bound() const { return box_; }

  tile_coord offset_in_box(const tile_id &coord) {
    auto minx = box_.min.x;
    auto miny = box_.min.y;
    return tile_coord{coord.x - minx, coord.y - miny};
  }

protected:
  tile_bounds box_;
};

} // namespace nik
} // namespace flywave