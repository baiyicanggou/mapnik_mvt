#ifndef MAPNIK_RASTER_C_API_H
#define MAPNIK_RASTER_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define RASTERCAPICALL __declspec(dllexport)
#else
#define RASTERCAPICALL
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

const int RASTER_DTYPE_RGBA8 = 0;
const int RASTER_DTYPE_GRAY8 = 1;
const int RASTER_DTYPE_GRAY8S = 2;
const int RASTER_DTYPE_GRAY16 = 3;
const int RASTER_DTYPE_GRAY16S = 4;
const int RASTER_DTYPE_GRAY32 = 5;
const int RASTER_DTYPE_GRAY32S = 6;
const int RASTER_DTYPE_GRAY32F = 7;
const int RASTER_DTYPE_GRAY64 = 8;
const int RASTER_DTYPE_GRAY64S = 9;
const int RASTER_DTYPE_GRAY64F = 10;

typedef struct _mapnik_raster_t mapnik_raster_t;
typedef struct _mapnik_raster_data_t mapnik_raster_data_t;
typedef struct _mapnik_raster_tiled_data_t raster_tiled_data_t;

RASTERCAPICALL mapnik_raster_t *mapnik_raster_new(int width, int height,
                                                  int type);
RASTERCAPICALL void mapnik_raster_free(mapnik_raster_t *m);
RASTERCAPICALL void mapnik_raster_copy_data(mapnik_raster_t *m,
                                            const uint8_t *data, int size);
RASTERCAPICALL const char *mapnik_raster_last_error(mapnik_raster_t *i);
RASTERCAPICALL int mapnik_raster_type(mapnik_raster_t *m);

RASTERCAPICALL mapnik_raster_data_t *
mapnik_raster_data_new(mapnik_raster_t *raster, double *bbox,
                       unsigned tile_size);
RASTERCAPICALL void mapnik_raster_data_free(mapnik_raster_data_t *m);
RASTERCAPICALL double *mapnik_raster_data_extent(mapnik_raster_data_t *m,
                                                 double *bbox);

RASTERCAPICALL raster_tiled_data_t *
mapnik_raster_tiled_data_new(mapnik_raster_data_t **raster, unsigned row,
                             unsigned col, unsigned tile_size);
RASTERCAPICALL void mapnik_raster_tiled_data_free(raster_tiled_data_t *m);

#ifdef __cplusplus
}
#endif

#endif // MAPNIK_RASTER_C_API_H