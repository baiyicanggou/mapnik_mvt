#pragma once

#include "raster_datasource.hh"

#include <mapnik/image_any.hpp>

#include <string>

namespace flywave {
namespace nik {

class raster_data {
public:
  raster_data(mapnik::image_any const &data,
              const mapnik::box2d<double> &extent);
  raster_data(const raster_data &rhs);
  raster_data &operator=(const raster_data &rhs);

  inline mapnik::box2d<double> const &envelope() const { return extent_; }

  template <typename Image> inline Image &get() {
    return data_.template get<Image>();
  }

  template <typename Image> inline const Image &get() const {
    return data_.template get<Image>();
  }

  inline mapnik::image_any const &data() const { return data_; }

  inline mapnik::image_dtype type() const { return data_.get_dtype(); }

  inline unsigned width() const { return data_.width(); }

  inline unsigned height() const { return data_.height(); }

private:
  void swap(raster_data &other);

  mapnik::image_any data_;
  mapnik::box2d<double> extent_;
};

} // namespace nik
} // namespace flywave
