#pragma once

#include <cmath>
#include <string>
#include <vector>

namespace mapnik {
template <typename T> class box2d;
} // namespace mapnik

namespace flywave {
namespace nik {

const unsigned short int TILE_SIZE = 256;
const unsigned short int MASK_SIZE = 256;

struct tile_id {
  tile_id() = default;

  tile_id(uint32_t _x, uint32_t _y, uint32_t _z) : x(_x), y(_y), z(_z) {}

  inline bool valid() const noexcept {
    uint32_t max_coord = std::pow(2u, z);
    return x < max_coord && y < max_coord;
  }

  uint32_t x{0};
  uint32_t y{0};
  uint32_t z{0};
};

inline bool operator==(const tile_id &x, const tile_id &y) {
  return x.x == y.x && x.y == y.y && x.z == y.z;
}

inline bool operator!=(const tile_id &x, const tile_id &y) { return !(x == y); }

std::ostream &operator<<(std::ostream &os, const tile_id &tile_id);

inline tile_id get_upper_zoom(const tile_id &t_id, uint32_t dz = 1) {
  if (dz == 1) {
    return tile_id{t_id.x / 2, t_id.y / 2, t_id.z - 1};
  }
  if (dz >= t_id.z) {
    return tile_id{0, 0, 0};
  }
  uint32_t coord_div = std::pow(2u, dz);
  return tile_id{t_id.x / coord_div, t_id.y / coord_div, t_id.z - dz};
}

class tile_ext_id {
public:
  tile_ext_id() = default;

  tile_ext_id(const tile_id &id, uint32_t size = 1) {
    if (size == 1) {
      lt_tile_ = id;
    } else {
      from_tile_id(id, size, size);
    }
  }

  tile_ext_id(const tile_id &id, uint32_t width, uint32_t height) {
    from_tile_id(id, width, height);
  }

  std::vector<tile_id> tile_ids() const noexcept {
    std::vector<tile_id> ids;
    ids.reserve(width_ * height_);
    for (uint32_t y = lt_tile_.y; y < lt_tile_.y + height_; ++y) {
      for (uint32_t x = lt_tile_.x; x < lt_tile_.x + width_; ++x) {
        ids.emplace_back(x, y, lt_tile_.z);
      }
    }
    return ids;
  }

  inline const tile_id &id() const noexcept { return lt_tile_; }

  inline const tile_id &left_top() const noexcept { return lt_tile_; }

  inline uint32_t width() const noexcept { return width_; }

  inline uint32_t height() const noexcept { return height_; }

  inline bool contains(const tile_id &tile_id) const noexcept {
    return tile_id.z == lt_tile_.z && tile_id.x >= lt_tile_.x &&
           tile_id.x < lt_tile_.x + width_ && tile_id.y >= lt_tile_.y &&
           tile_id.y < lt_tile_.y + height_;
  }

  mapnik::box2d<double> get_bbox() const;

private:
  void from_tile_id(const tile_id &id, uint32_t width, uint32_t height);

  tile_id lt_tile_{0, 0, 0};
  uint32_t width_{1};
  uint32_t height_{1};
};

inline bool operator==(const tile_ext_id &x, const tile_ext_id &y) {
  return x.left_top() == y.left_top() && x.width() == y.width() &&
         x.height() == y.height();
}

inline bool operator!=(const tile_ext_id &x, const tile_ext_id &y) {
  return !(x == y);
}

std::ostream &operator<<(std::ostream &os, const tile_ext_id &metatile_id);

struct tile_data {
  tile_id id;
  std::string data;
};

struct tile {
  tile_id _id;

public:
  tile() : _id() {}
  tile(const tile_id &coord) : _id(coord) {}

  const tile_id &id() const { return _id; }

  tile_id &id() { return _id; }

  virtual ~tile(){};
};

struct mapnik_tile {
  mapnik_tile() = default;

  mapnik_tile(const tile_ext_id &_id)
      : id(_id), tiles(_id.width() * _id.height()) {
    const tile_id &left_top = id.left_top();
    std::size_t pos = 0;
    for (uint32_t y = left_top.y; y < left_top.y + id.height(); ++y) {
      for (uint32_t x = left_top.x; x < left_top.x + id.width(); ++x) {
        tile_id &tile_id = tiles[pos++].id;
        tile_id.x = x;
        tile_id.y = y;
        tile_id.z = left_top.z;
      }
    }
  }
 
  virtual ~mapnik_tile()=default;
  bool validate() const noexcept;

  tile_ext_id id;
  std::vector<tile_data> tiles;
};

} // namespace nik
} // namespace flywave
