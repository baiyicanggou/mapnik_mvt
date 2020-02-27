#include "raster_data.hh"

namespace flywave {
namespace nik {

raster_data::raster_data(mapnik::image_any const &data,
                         mapnik::box2d<double> const &extent)
    : data_(data), extent_(extent) {}

raster_data::raster_data(const raster_data &rhs)
    : data_(rhs.data_), extent_(rhs.extent_) {}

void raster_data::swap(raster_data &other) {
  std::swap(data_, other.data_);
  std::swap(extent_, other.extent_);
}

raster_data &raster_data::operator=(const raster_data &rhs) {
  raster_data tmp(rhs);
  swap(tmp);
  return *this;
}
} // namespace nik
} // namespace flywave
