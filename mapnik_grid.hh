#pragma once

#include <cmath>
#include <exception>

#include "spherical_mercator.hh"

#include "grid.hh"
#include "tile.hh"
#include "util.hh"

namespace flywave {
namespace nik {

class mapnik_geodetic_grid : public nik::grid {
public:
  mapnik_geodetic_grid(unsigned int tileSize, const mapnik::box2d<double> box,
                       bool up_order = false, bool tmsCompatible = false,
                       float zoomFactor = 2)
      : nik::grid(tileSize, box, cSRS, up_order, (tmsCompatible) ? 2 : 1,
                  zoomFactor) {}

protected:
  static const mapnik::projection cSRS;
};

class global_geodetic : public mapnik_geodetic_grid {
public:
  global_geodetic(unsigned int tileSize = nik::TILE_SIZE)
      : mapnik_geodetic_grid(tileSize,
                             mapnik::box2d<double>({-180, -90}, {180, 90})) {}

  global_geodetic(const mapnik::box2d<double> box,
                  unsigned int tileSize = nik::TILE_SIZE)
      : mapnik_geodetic_grid(tileSize,
                             mapnik::box2d<double>({-180, -90}, {180, 90})) {
    this->_local_extent = box;
  }
};

class mapnik_mercator_grid : public nik::grid {
public:
  mapnik_mercator_grid(unsigned int tileSize, const mapnik::box2d<double> box,
                       bool up_order = false, unsigned short int rootTiles = 1,
                       float zoomFactor = 2)
      : grid(tileSize, box, cSRS, up_order, rootTiles, zoomFactor) {}

  static const unsigned int cSemiMajorAxis;

  static const double cEarthCircumference;

  static const double cOriginShift;

  static const mapnik::projection cSRS;
};

class global_mercator : public mapnik_mercator_grid {
public:
  global_mercator(unsigned int tileSize = nik::TILE_SIZE)
      : mapnik_mercator_grid(
            tileSize, mapnik::box2d<double>({-cOriginShift, -cOriginShift},
                                            {cOriginShift, cOriginShift})) {}
  global_mercator(const mapnik::box2d<double> box,
                  unsigned int tileSize = nik::TILE_SIZE)
      : mapnik_mercator_grid(
            tileSize, mapnik::box2d<double>({-cOriginShift, -cOriginShift},
                                            {cOriginShift, cOriginShift})) {
    this->_local_extent = box;
  }
};

} // namespace nik
} // namespace flywave