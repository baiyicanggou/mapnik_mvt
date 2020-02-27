#include "datasource_c_api.h"
#include "datasource_impl.hh"

#include "cached_datasource.hh"
#include "datasource_impl.hh"
#include "feature_impl.hh"
#include "geometry_datasource.hh"
#include "make_geometry_datasource.hh"
#include "make_raster_datasource.hh"
#include "raster_datasource.hh"
#include "raster_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

mapnik_datasource_t *
mapnik_geometry_datasource(mapnik_feature_collection_t *feature) {
  mapnik::datasource_ptr ptr =
      flywave::nik::make_geometry_datasource(feature->fc);
  mapnik_datasource_t *map = new mapnik_datasource_t{ptr};
  return map;
}

mapnik_datasource_t *mapnik_raster_datasource(mapnik_raster_data_t *raster) {
  mapnik::datasource_ptr ptr =
      flywave::nik::make_raster_datasource(raster->ds, raster->tile_size);
  mapnik_datasource_t *map = new mapnik_datasource_t{ptr};
  return map;
}

mapnik_datasource_t *
mapnik_tiled_raster_datasource(raster_tiled_data_t *raster) {
  mapnik::datasource_ptr ptr = flywave::nik::make_raster_datasource(
      raster->ds, raster->extent, raster->row, raster->col, raster->tile_size);
  mapnik_datasource_t *map = new mapnik_datasource_t{ptr};
  return map;
}

int mapnik_datasource_type(mapnik_datasource_t *m) {
  if (m != NULL) {
    return m->ptr->type();
  }
  return -1;
}

double *mapnik_datasource_envelope(mapnik_datasource_t *m, double *bbox) {
  if (m != NULL) {
    mapnik::box2d<double> b = m->ptr->envelope();
    bbox[0] = b.minx();
    bbox[1] = b.miny();
    bbox[2] = b.maxx();
    bbox[3] = b.maxy();
    return bbox;
  }
  return NULL;
}

void mapnik_datasource_free(mapnik_datasource_t *m) {
  if (m != NULL) {
    delete m;
  }
}

#ifdef __cplusplus
}
#endif
