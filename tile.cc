#include "tile.hh"
#include "spherical_mercator.hh"

#include <cassert>
#include <ostream>

#include <mapnik/box2d.hpp>
#include <mapnik/well_known_srs.hpp>

namespace flywave {
namespace nik {

std::ostream &operator<<(std::ostream &os, const tile_id &tile_id) {
  return os << "x: " << tile_id.x << " y: " << tile_id.y << " z: " << tile_id.z;
}

std::ostream &operator<<(std::ostream &os, const tile_ext_id &metatile_id) {
  return os << "left top: " << metatile_id.left_top()
            << " width: " << metatile_id.width()
            << " height: " << metatile_id.height();
}

void tile_ext_id::from_tile_id(const tile_id &id, uint32_t width,
                               uint32_t height) {
  assert(id.valid());
  uint32_t zoom_size = std::pow(2u, id.z);

  uint32_t x;
  if (width <= 1) {
    x = id.x;
    width_ = width;
  } else if (width > zoom_size) {
    x = 0;
    width_ = zoom_size;
  } else {
    x = id.x - id.x % width;
    uint32_t dx = zoom_size - x;
    width_ = dx < width ? dx : width;
  }

  uint32_t y;
  if (height <= 1) {
    y = id.y;
    height_ = height;
  } else if (height > zoom_size) {
    y = 0;
    height_ = zoom_size;
  } else {
    y = id.y - id.y % height;
    uint32_t dy = zoom_size - y;
    height_ = dy < height ? dy : height;
  }

  lt_tile_ = tile_id{x, y, id.z};
}

mapnik::box2d<double> tile_ext_id::get_bbox() const {
  const uint32_t tile_size = 256;
  spherical_mercator<20> merc(tile_size);
  double minx = lt_tile_.x * tile_size;
  double miny = (lt_tile_.y + height_) * tile_size;
  double maxx = (lt_tile_.x + width_) * tile_size;
  double maxy = lt_tile_.y * tile_size;
//  double shift = std::pow(2.0, lt_tile_.z) * tile_size;
  merc.from_pixels(minx, miny, lt_tile_.z);
  merc.from_pixels(maxx, maxy, lt_tile_.z);
  mapnik::lonlat2merc(&minx, &miny, 1);
  mapnik::lonlat2merc(&maxx, &maxy, 1);
  return mapnik::box2d<double>(minx, miny, maxx, maxy);
}

bool mapnik_tile::validate() const noexcept {
  std::size_t num_tiles = tiles.size();
  if ((id.width() * id.height()) != num_tiles) {
    return false;
  }
  std::vector<tile_id> ids = id.tile_ids();
  assert(ids.size() == num_tiles);
  std::size_t i = 0;
  for (const tile_id &tile_id : ids) {
    if (tile_id != tiles[i++].id) {
      return false;
    }
  }
  return true;
}

} // namespace nik
} // namespace flywave
