#include "raster_c_api.h"
#include "raster_impl.hh"

#include <cassert>

#ifdef __cplusplus
extern "C" {
#endif

mapnik_raster_t *mapnik_raster_new(int width, int height, int type) {
  mapnik_raster_t *m = new mapnik_raster_t{mapnik::create_image_any(
      width, height, static_cast<mapnik::image_dtype>(type), true)};
  return m;
}

void mapnik_raster_free(mapnik_raster_t *m) {
  if (m) {
    if (m->err) {
      delete m->err;
    }
    delete m;
  }
}

void mapnik_raster_copy_data(mapnik_raster_t *m, const uint8_t *data,
                             int size) {
  if (m && m->data.size() == size) {
    memcpy(m->data.bytes(), data, size);
  }
}

const char *mapnik_raster_last_error(mapnik_raster_t *i) {
  if (i && i->err) {
    return i->err->c_str();
  }
  return NULL;
}

int mapnik_raster_type(mapnik_raster_t *m) {
  if (m) {
    return m->data.get_dtype();
  }
  return -1;
}

mapnik_raster_data_t *mapnik_raster_data_new(mapnik_raster_t *raster,
                                             double *bbox, unsigned tile_size) {
  mapnik::box2d<double> b{bbox[0], bbox[1], bbox[2], bbox[3]};
  mapnik_raster_data_t *m = new mapnik_raster_data_t{
      std::make_shared<flywave::nik::raster_data>(raster->data, b), tile_size};
  return m;
}

void mapnik_raster_data_free(mapnik_raster_data_t *m) {
  if (m) {
    delete m;
  }
}

double *mapnik_raster_data_extent(mapnik_raster_data_t *m, double *bbox) {
  if (m) {
    mapnik::box2d<double> b = m->ds->envelope();
    bbox[0] = b.minx();
    bbox[1] = b.miny();
    bbox[2] = b.maxx();
    bbox[3] = b.maxy();
    return bbox;
  }
  return NULL;
}

raster_tiled_data_t *mapnik_raster_tiled_data_new(mapnik_raster_data_t **raster,
                                                  unsigned row, unsigned col,
                                                  unsigned tile_size) {
  std::vector<std::shared_ptr<flywave::nik::raster_data>> ds;
  mapnik::box2d<double> extent;
  for (int i = 0; i < row * col; i++) {
    extent.expand_to_include(raster[i]->ds->envelope());
    ds.emplace_back(raster[i]->ds);
  }
  raster_tiled_data_t *m =
      new raster_tiled_data_t{std::move(ds), extent, row, col, tile_size};
  return m;
}

void mapnik_raster_tiled_data_free(raster_tiled_data_t *m) {
  if (m) {
    delete m;
  }
}

#ifdef __cplusplus
}
#endif
