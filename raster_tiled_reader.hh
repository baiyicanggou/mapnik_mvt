#pragma once

#include "raster_datasource.hh"

#include <mapnik/image_any.hpp>

#include <memory>
#include <string>

namespace flywave {
namespace nik {

class raster_tiled_reader {
protected:
  raster_data_ptr _data;
  mapnik::box2d<double> _tile_box;
  unsigned _tile_width;
  unsigned _tile_height;

public:
  explicit raster_tiled_reader(raster_data_ptr info,
                               mapnik::box2d<double> tile_box,
                               unsigned tile_width, unsigned tile_height)
      : _data(info), _tile_box(tile_box), _tile_height(tile_height),
        _tile_width(tile_width) {}

  unsigned width() const { return _tile_width; }
  unsigned height() const { return _tile_height; }

  mapnik::box2d<double> envelope() const { return _tile_box; }

  mapnik::image_any read(unsigned x, unsigned y, unsigned width,
                         unsigned height) const;
};

typedef std::shared_ptr<raster_tiled_reader> raster_tiled_reader_ptr;

} // namespace nik
} // namespace flywave
