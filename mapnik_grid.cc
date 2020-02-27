#include "mapnik_grid.hh"
#include <mapnik/well_known_srs.hpp>

namespace flywave {
namespace nik {

const unsigned int mapnik_mercator_grid::cSemiMajorAxis = 6378137;
const double mapnik_mercator_grid::cEarthCircumference =
    2 * M_PI * mapnik_mercator_grid::cSemiMajorAxis;
const double mapnik_mercator_grid::cOriginShift =
    mapnik_mercator_grid::cEarthCircumference / 2.0;

static mapnik::projection set_3857_SRS(void) {
  mapnik::projection srs(mapnik::MAPNIK_GMERC_PROJ);
  return srs;
}

const mapnik::projection mapnik_mercator_grid::cSRS = set_3857_SRS();

static mapnik::projection set_4326_SRS(void) {
  mapnik::projection srs(mapnik::MAPNIK_LONGLAT_PROJ);
  return srs;
}

const mapnik::projection mapnik_geodetic_grid::cSRS = set_4326_SRS();

} // namespace nik
} // namespace flywave