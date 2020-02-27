#pragma once

#include <deque>
#include <vector>

#include <mapnik/featureset.hpp>
#include <mapnik/geometry.hpp>

#include "raster_data.hh"
#include "raster_datasource.hh"

namespace flywave {
namespace nik {

mapnik::datasource_ptr make_raster_datasource(std::shared_ptr<raster_data> ds,
                                              unsigned tile_size);

mapnik::datasource_ptr
make_raster_datasource(std::vector<std::shared_ptr<raster_data>> ds,
                       mapnik::box2d<double> extent, unsigned row, unsigned col,
                       unsigned tile_size);

} // namespace nik
} // namespace flywave
