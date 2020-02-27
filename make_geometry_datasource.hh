#pragma once

#include <deque>
#include <vector>

#include <mapnik/featureset.hpp>

#include "geometry_datasource.hh"

namespace flywave {
namespace nik {

mapnik::datasource_ptr make_geometry_datasource(feature_collection<double> ds);

} // namespace nik
} // namespace flywave
