#ifndef MAPNIK_DATASOURCE_C_API_H
#define MAPNIK_DATASOURCE_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define MAPNIKCAPICALL __declspec(dllexport)
#else
#define MAPNIKCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

const int DATASOURCE_VECTOR = 0;
const int DATASOURCE_RASTER = 1;

typedef struct _mapnik_datasource_t mapnik_datasource_t;
typedef struct _mapnik_feature_collection_t mapnik_feature_collection_t;
typedef struct _mapnik_raster_data_t mapnik_raster_data_t;
typedef struct _mapnik_raster_tiled_data_t raster_tiled_data_t;

MAPNIKCAPICALL mapnik_datasource_t *
mapnik_geometry_datasource(mapnik_feature_collection_t *feature);
MAPNIKCAPICALL mapnik_datasource_t *
mapnik_raster_datasource(mapnik_raster_data_t *raster);
MAPNIKCAPICALL mapnik_datasource_t *
mapnik_tiled_raster_datasource(raster_tiled_data_t *raster);

MAPNIKCAPICALL int mapnik_datasource_type(mapnik_datasource_t *m);
MAPNIKCAPICALL double *mapnik_datasource_envelope(mapnik_datasource_t *m,
                                                  double *bbox);

MAPNIKCAPICALL void mapnik_datasource_free(mapnik_datasource_t *m);

#ifdef __cplusplus
}
#endif

#endif // MAPNIK_DATASOURCE_C_API_H