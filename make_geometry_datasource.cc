#include "make_geometry_datasource.hh"

namespace flywave {
namespace nik {

mapnik::datasource_ptr make_geometry_datasource(feature_collection<double> ds) {
  return std::make_shared<geometry_datasource>(ds);
}

} // namespace nik
} // namespace flywave
