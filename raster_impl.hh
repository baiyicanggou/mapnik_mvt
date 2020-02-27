#ifndef MAPNIK_RASTER_IMPL_H
#define MAPNIK_RASTER_IMPL_H

#include "raster_data.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _mapnik_raster_t {
  mapnik::image_any data;
  std::string *err;
};

struct _mapnik_raster_data_t {
  std::shared_ptr<flywave::nik::raster_data> ds;
  unsigned tile_size;
};

struct _mapnik_raster_tiled_data_t {
  std::vector<std::shared_ptr<flywave::nik::raster_data>> ds;
  mapnik::box2d<double> extent;
  unsigned row;
  unsigned col;
  unsigned tile_size;
};

#ifdef __cplusplus
}
#endif

#endif