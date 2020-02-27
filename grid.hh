#pragma once

#include <cmath>

#include <memory>

#include "spherical_mercator.hh"

#include "tile.hh"
#include "util.hh"

#include <mapnik/box2d.hpp>
#include <mapnik/coord.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/projection.hpp>

namespace flywave {
namespace nik {

class grid {
protected:
  void init() {
    _initial_resolution = _extent.width() / _rootTiles / _tile_size;

    _x_origin_shift = _extent.width() / 2;
    _y_origin_shift = _extent.height() / 2;
    _local_extent = _extent;
  }

public:
  grid(bool up_order = false)
      : up_order_(up_order), _tile_size(256), _zoom_factor(2),
        _srs(nik::default_map_proj), _proj(nik::default_map_proj) {
    init();
  }

  virtual ~grid() {}

  grid(unsigned int tile_size, const mapnik::box2d<double> extent,
       const mapnik::projection &srs, bool up_order = false,
       unsigned short int rootTiles = 1, float zoomFactor = 2)
      : _tile_size(tile_size), _rootTiles(rootTiles), _extent(extent),
        up_order_(up_order), _zoom_factor(zoomFactor), _proj(srs) {
    if (srs.well_known()) {
      _srs = srs.well_known()->as_string();
    }
    init();
  }

  grid(unsigned int tile_size, const mapnik::box2d<double> extent,
       bool up_order = false, unsigned short int rootTiles = 1,
       float zoomFactor = 2)
      : _tile_size(tile_size), _rootTiles(rootTiles), _extent(extent),
        up_order_(up_order), _zoom_factor(zoomFactor),
        _srs(nik::default_map_proj), _proj(nik::default_map_proj) {
    init();
  }

  grid &operator=(const grid &other) {
    _tile_size = other._tile_size;
    _extent = other._extent;
    _local_extent = other._local_extent;
    up_order_ = other.up_order_;
    _srs = other._srs;
    _initial_resolution = other._initial_resolution;
    _x_origin_shift = other._x_origin_shift;
    _y_origin_shift = other._y_origin_shift;
    _zoom_factor = other._zoom_factor;
    return *this;
  }

  bool operator==(const grid &other) const {
    return _tile_size == other._tile_size && _extent == other._extent &&
           _srs == other._srs && _local_extent == other._local_extent &&
           _initial_resolution == other._initial_resolution &&
           _x_origin_shift == other._x_origin_shift &&
           _y_origin_shift == other._y_origin_shift &&
           up_order_ == other.up_order_ && _zoom_factor == other._zoom_factor;
  }

  virtual inline double resolution(uint8_t zoom) const {
    return _initial_resolution / std::pow(_zoom_factor, zoom);
  }

  inline uint8_t zoom_for_resolution(double resolution) const {
    return (uint8_t)std::ceil(
        (std::log(_initial_resolution) / std::log(_zoom_factor)) -
        (std::log(resolution) / std::log(_zoom_factor)));
  }

  inline nik::tile_coord
  pixels_to_tile_max(const nik::pixel_coord &pixel) const {
    unsigned int tx = (unsigned int)(pixel.x / _tile_size),
                 ty = (unsigned int)(pixel.y / _tile_size);
    if (tx * _tile_size < pixel.x)
      tx++;
    if (ty * _tile_size < pixel.y)
      ty++;
    return nik::tile_coord(tx, ty);
  }

  inline nik::tile_coord
  pixels_to_tile_min(const nik::pixel_coord &pixel) const {
    unsigned int tx = (unsigned int)(pixel.x / _tile_size),
                 ty = (unsigned int)(pixel.y / _tile_size);
    if (pixel.x % _tile_size == (_tile_size - 1))
      tx++;
    if (pixel.y % _tile_size == (_tile_size - 1))
      ty++;

    return nik::tile_coord(tx, ty);
  }

  inline mapnik::coord<double, 2> pixels_to_crs(const nik::pixel_coord &pixel,
                                                uint8_t zoom) const {
    double res = resolution(zoom);

    auto rx = (pixel.x * res) - _x_origin_shift;
    double ry;
    if (up_order_) {
      ry = (pixel.y * res) - _y_origin_shift;
    } else {
      ry = _y_origin_shift - (pixel.y * res);
    }
    return mapnik::coord<double, 2>(rx, ry);
  }

  inline nik::pixel_coord crs_to_pixels(const mapnik::coord<double, 2> &coord,
                                        uint8_t zoom) const {
    double res = resolution(zoom);
    unsigned int px = (_x_origin_shift + coord.x) / res;
    uint32_t py;
    if (up_order_) {
      py = (_y_origin_shift + coord.y) / res;
    } else {
      py = (_y_origin_shift - coord.y) / res;
    }
    return nik::pixel_coord(px, py);
  }

  inline tile_id crs_to_tile_max(const mapnik::coord<double, 2> &coord,
                                 uint8_t zoom) const {
    const nik::pixel_coord pixel = crs_to_pixels(coord, zoom);
    nik::tile_coord tile = pixels_to_tile_max(pixel);

    return tile_id(tile.x, tile.y, zoom);
  }

  inline tile_id crs_to_tile_min(const mapnik::coord<double, 2> &coord,
                                 uint8_t zoom) const {
    const nik::pixel_coord pixel = crs_to_pixels(coord, zoom);
    nik::tile_coord tile = pixels_to_tile_min(pixel);

    return tile_id(tile.x, tile.y, zoom);
  }

  virtual inline mapnik::box2d<double> tile_bounds(const tile_id &coord) const {
    if (up_order_) {
      const nik::pixel_coord minxy(coord.x * _tile_size, coord.y * _tile_size),
          maxxy((coord.x + 1) * _tile_size, (coord.y + 1) * _tile_size);
      const mapnik::coord<double, 2> lowerLeft = pixels_to_crs(minxy, coord.z),
                                     upperRight = pixels_to_crs(maxxy, coord.z);
      return mapnik::box2d<double>(lowerLeft, upperRight);
    } else {
      const nik::pixel_coord minxy(coord.x * _tile_size,
                                   (coord.y + 1) * _tile_size),
          maxxy((coord.x + 1) * _tile_size, (coord.y) * _tile_size);
      const mapnik::coord<double, 2> lowerLeft = pixels_to_crs(minxy, coord.z),
                                     upperRight = pixels_to_crs(maxxy, coord.z);
      return mapnik::box2d<double>(lowerLeft, upperRight);
    }
  }

  inline unsigned int tile_size() const { return _tile_size; }

  inline const std::string &srs() const { return _srs; }

  inline const mapnik::box2d<double> &get_extent() const { return _extent; }

  inline nik::tile_bounds get_tile_extent(uint8_t zoom) const {
    auto ll =
        mapnik::coord<double, 2>{_local_extent.minx(), _local_extent.miny()};
    auto ur =
        mapnik::coord<double, 2>{_local_extent.maxx(), _local_extent.maxy()};
    if (up_order_) {
      tile_id ll_id = crs_to_tile_min(ll, zoom),
              ur_id = crs_to_tile_max(ur, zoom);

      if (ll_id.x == ur_id.x)
        ur_id.x++;
      if (ll_id.y == ur_id.y)
        ur_id.y++;
      return nik::tile_bounds{{ll_id.x, ll_id.y}, {ur_id.x, ur_id.y}};
    } else {
      tile_id ll_id =
                  crs_to_tile_min(mapnik::coord<double, 2>{ll.x, ur.y}, zoom),
              ur_id =
                  crs_to_tile_max(mapnik::coord<double, 2>{ur.x, ll.y}, zoom);
      if (ll_id.x == ur_id.x)
        ur_id.x++;
      if (ll_id.y == ur_id.y)
        ur_id.y++;
      return nik::tile_bounds{{ll_id.x, ll_id.y}, {ur_id.x, ur_id.y}};
    }
  }

  inline bool up_order() const { return up_order_; }

  inline void set_up_order(bool order) { up_order_ = order; }

  inline const mapnik::projection &reference() const { return _proj; }

  mapnik::box2d<double> get_bbox(const tile_ext_id &id) const {
    auto &tid = id.id();
    auto box = tile_bounds(tid);
    auto xmin = box.minx();
    auto ymin = box.miny();

    auto xmax = box.maxx();
    auto ymax = box.maxy();
    flywave::merc2lonlat(&xmin, &ymin, 1);
    flywave::merc2lonlat(&xmax, &ymax, 1);
    return std::move(box);
  }

protected:
  friend class grid_iterator;

  unsigned short int _rootTiles;

  unsigned int _tile_size;

  mapnik::box2d<double> _extent;
  mapnik::box2d<double> _local_extent;

  std::string _srs;

  double _initial_resolution, _x_origin_shift, _y_origin_shift;

  float _zoom_factor;
  bool up_order_;

  mapnik::projection _proj;
};
} // namespace nik
} // namespace flywave
