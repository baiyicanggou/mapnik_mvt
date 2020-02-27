#ifndef TILER_C_API_H
#define TILER_C_API_H

#include "stdint.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define TILERCAPICALL __declspec(dllexport)
#else
#define TILERCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mapnik_map_t mapnik_map_t;
typedef struct _mapnik_image_t mapnik_image_t;
typedef struct _mapnik_datasource_t mapnik_datasource_t;
typedef struct _mapnik_tile_t mapnik_tile_t;
typedef struct _mapnik_tiler_t mapnik_tiler_t;
typedef struct _mapnik_tiler_options_t mapnik_tiler_options_t;

typedef struct _tiler_source_t tiler_source_t;
typedef struct _tiler_grid_t tiler_grid_t;
typedef struct _tiler_source_options_t tiler_source_options_t;

TILERCAPICALL tiler_source_options_t *tiler_source_options_new();
TILERCAPICALL void tiler_source_options_free(tiler_source_options_t *m);
TILERCAPICALL void tiler_source_options_add(tiler_source_options_t *m,
                                            const char *name,
                                            mapnik_map_t *map);

TILERCAPICALL tiler_source_t *tiler_source_new(tiler_source_options_t *opts);
TILERCAPICALL void tiler_source_free(tiler_source_t *m);
TILERCAPICALL void tiler_source_add_datasource(tiler_source_t *m,
                                               const char *name,
                                               mapnik_datasource_t *ds);

TILERCAPICALL tiler_grid_t *tiler_global_geodetic_grid(unsigned int tileSize);
TILERCAPICALL tiler_grid_t *tiler_global_mercator_grid(unsigned int tileSize);

TILERCAPICALL tiler_grid_t *
tiler_global_geodetic_local_grid(unsigned int tileSize, double *box);
TILERCAPICALL tiler_grid_t *
tiler_global_mercator_local_grid(unsigned int tileSize, double *box);

TILERCAPICALL tiler_grid_t *tiler_geodetic_grid(unsigned int tileSize,
                                                double *box);
TILERCAPICALL tiler_grid_t *tiler_mercator_grid(unsigned int tileSize,
                                                double *box);
TILERCAPICALL void tiler_grid_free(tiler_grid_t *m);

// mapnik tiler options
TILERCAPICALL mapnik_tiler_options_t *
mapnik_tiler_options_new(const char *style);
TILERCAPICALL void mapnik_tiler_options_add_layer(mapnik_tiler_options_t *m,
                                                  const char *name);
TILERCAPICALL void mapnik_tiler_options_free(mapnik_tiler_options_t *m);

// mapnik tiler
TILERCAPICALL mapnik_tiler_t *mapnik_tiler_new(tiler_source_t *source,
                                               tiler_grid_t *grid,
                                               mapnik_tiler_options_t *opts);
TILERCAPICALL void mapnik_tiler_free(mapnik_tiler_t *m);

TILERCAPICALL void mapnik_tiler_render(mapnik_tiler_t *m,
                                       unsigned int startZoom,
                                       unsigned int endZoom, void *data);

TILERCAPICALL void mapnik_tiler_render_select(mapnik_tiler_t *m,
                                              uint16_t *zooms, int count,
                                              void *data);

// mvt tiler options
typedef struct _mvt_tiler_options_t mvt_tiler_options_t;

typedef struct _mvt_tiler_t mvt_tiler_t;
typedef struct _mvt_tile_t mvt_tile_t;

TILERCAPICALL mvt_tiler_options_t *mvt_tiler_options_new(const char *style);
TILERCAPICALL void mvt_tiler_options_add_layer(mvt_tiler_options_t *m,
                                               const char *name);
TILERCAPICALL void mvt_tiler_options_free(mvt_tiler_options_t *m);

// mvt tiler
TILERCAPICALL mvt_tiler_t *mvt_tiler_new(tiler_source_t *source,
                                         tiler_grid_t *grid,
                                         mvt_tiler_options_t *opts);
TILERCAPICALL void mvt_tiler_free(mvt_tiler_t *m);

TILERCAPICALL void mvt_tiler_render(mvt_tiler_t *m, unsigned int startZoom,
                                    unsigned int endZoom, void *data);

TILERCAPICALL void mvt_tiler_render_select(mvt_tiler_t *m, uint16_t *zooms,
                                           int count, void *data);

// utfgrid tiler options
typedef struct _utfgrid_tiler_options_t utfgrid_tiler_options_t;

typedef struct _utfgrid_tiler_t utfgrid_tiler_t;
typedef struct _utfgrid_tile_t utfgrid_tile_t;

TILERCAPICALL utfgrid_tiler_options_t *
utfgrid_tiler_options_new(const char *style);
TILERCAPICALL void utfgrid_tiler_options_add_layer(utfgrid_tiler_options_t *m,
                                                   const char *name);
TILERCAPICALL void utfgrid_tiler_options_free(utfgrid_tiler_options_t *m);

// utfgrid tiler
TILERCAPICALL utfgrid_tiler_t *utfgrid_tiler_new(tiler_source_t *source,
                                                 tiler_grid_t *grid,
                                                 utfgrid_tiler_options_t *opts);
TILERCAPICALL void utfgrid_tiler_free(utfgrid_tiler_t *m);

TILERCAPICALL void utfgrid_tiler_render(utfgrid_tiler_t *m,
                                        unsigned int startZoom,
                                        unsigned int endZoom, void *data);

TILERCAPICALL void utfgrid_tiler_render_select(utfgrid_tiler_t *m,
                                               uint16_t *zooms, int count,
                                               void *data);

#ifdef __cplusplus
}
#endif

#endif // MAPNIK_C_API_H
