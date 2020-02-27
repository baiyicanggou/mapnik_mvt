#include "make_raster_datasource.hh"
#include "raster_datasource.hh"

namespace flywave {
namespace nik {

mapnik::datasource_ptr make_raster_datasource(std::shared_ptr<raster_data> ds,
                                              unsigned tile_size) {
  return std::make_shared<raster_datasource>(ds, tile_size);
}

mapnik::datasource_ptr
make_raster_datasource(std::vector<std::shared_ptr<raster_data>> ds,
                       mapnik::box2d<double> extent, unsigned row, unsigned col,
                       unsigned tile_size) {
  return std::make_shared<raster_datasource>(ds, extent, row, col, tile_size);
}

} // namespace nik
} // namespace flywave
