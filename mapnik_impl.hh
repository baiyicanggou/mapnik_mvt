#ifndef MAPNIK_IMPL_H
#define MAPNIK_IMPL_H

#include "feature.hh"
#include "mvt_tile.hh"
#include "tile.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _mapnik_bbox_t {
  mapnik::box2d<double> b;
};

struct _mapnik_map_t {
  mapnik::Map *m;
  std::string *err;
};

struct _mapnik_image_t {
  mapnik::image_rgba8 *i;
  std::string *err;
};

struct _mapnik_layer_t {
  mapnik::layer layer;
};

struct _mapnik_tile_t {
  flywave::nik::mapnik_tile data;
};

struct _mvt_tile_t {
  flywave::nik::mapnik_tile data;
};

struct _utfgrid_tile_t {
  flywave::nik::mapnik_tile data;
};

#ifdef __cplusplus
}
#endif

#endif
