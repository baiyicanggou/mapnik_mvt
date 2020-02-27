#ifndef MAPNIK_TILERENDER_C_API_H
#define MAPNIK_TILERENDER_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define TILERENDERCAPICALL __declspec(dllexport)
#else
#define TILERENDERCAPICALL
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mapnik_map_t mapnik_map_t;
typedef struct _mapnik_image_t mapnik_image_t;

typedef struct _mapnik_tile_t mapnik_tile_t;

TILERENDERCAPICALL mapnik_tile_t *mapnik_tile(uint32_t x, uint32_t y,
                                              uint32_t z, uint32_t width,
                                              uint32_t height);
TILERENDERCAPICALL void mapnik_tile_free(mapnik_tile_t *m);
TILERENDERCAPICALL int mapnik_tile_data_count(mapnik_tile_t *m);
TILERENDERCAPICALL const uint8_t *mapnik_tile_get_data(mapnik_tile_t *m, int i,
                                                       int *si, uint32_t *x,
                                                       uint32_t *y,
                                                       uint32_t *z);

typedef struct _mvt_tile_t mvt_tile_t;

TILERENDERCAPICALL mvt_tile_t *mvt_tile(uint32_t x, uint32_t y, uint32_t z,
                                        uint32_t width, uint32_t height);
TILERENDERCAPICALL void mvt_tile_free(mvt_tile_t *m);
TILERENDERCAPICALL int mvt_tile_data_count(mvt_tile_t *m);
TILERENDERCAPICALL const uint8_t *mvt_tile_get_data(mvt_tile_t *m, int i,
                                                    int *si, uint32_t *x,
                                                    uint32_t *y, uint32_t *z);

typedef struct _utfgrid_tile_t utfgrid_tile_t;

TILERENDERCAPICALL utfgrid_tile_t *utfgrid_tile(uint32_t x, uint32_t y,
                                                uint32_t z, uint32_t width,
                                                uint32_t height);
TILERENDERCAPICALL void utfgrid_tile_free(utfgrid_tile_t *m);
TILERENDERCAPICALL int utfgrid_tile_data_count(utfgrid_tile_t *m);
TILERENDERCAPICALL const uint8_t *
utfgrid_tile_get_data(utfgrid_tile_t *m, int i, int *si, uint32_t *x,
                      uint32_t *y, uint32_t *z);

#ifdef __cplusplus
}
#endif

#endif // MAPNIK_TILERENDER_C_API_H