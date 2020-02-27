#ifndef MAPNIK_FEATURE_C_API_H
#define MAPNIK_FEATURE_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define GEOAPICALL __declspec(dllexport)
#else
#define GEOAPICALL
#endif

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const int GEO_UNKNOWN;
extern const int GEO_POINT;
extern const int GEO_LINESTRING;
extern const int GEO_POLYGON;
extern const int GEO_MULTIPOINT;
extern const int GEO_MULTILINESTRING;
extern const int GEO_MULTIPOLYGON;
extern const int GEO_COLLECTION;

typedef struct _mapnik_identifier_t mapnik_identifier_t;
typedef struct _mapnik_property_value_t mapnik_property_value_t;
typedef struct _mapnik_property_map_t mapnik_property_map_t;

typedef struct _mapnik_geometry_t mapnik_geometry_t;
typedef struct _mapnik_feature_t mapnik_feature_t;
typedef struct _mapnik_feature_collection_t mapnik_feature_collection_t;

GEOAPICALL mapnik_identifier_t *mapnik_identifier_new_uint64(uint64_t id);
GEOAPICALL mapnik_identifier_t *mapnik_identifier_new_int64(int64_t id);
GEOAPICALL mapnik_identifier_t *mapnik_identifier_new_double(double id);
GEOAPICALL mapnik_identifier_t *mapnik_identifier_new_string(const char *id);
GEOAPICALL void mapnik_identifier_free(mapnik_identifier_t *m);

GEOAPICALL mapnik_property_value_t *mapnik_property_value_new();
GEOAPICALL mapnik_property_value_t *mapnik_property_value_new_bool(_Bool v);
GEOAPICALL mapnik_property_value_t *
mapnik_property_value_new_uint64(uint64_t v);
GEOAPICALL mapnik_property_value_t *mapnik_property_value_new_int64(int64_t v);
GEOAPICALL mapnik_property_value_t *mapnik_property_value_new_double(double v);
GEOAPICALL mapnik_property_value_t *
mapnik_property_value_new_string(const char *v);
GEOAPICALL void mapnik_property_value_free(mapnik_property_value_t *m);

GEOAPICALL mapnik_property_map_t *mapnik_property_map_new();
GEOAPICALL void mapnik_property_map_free(mapnik_property_map_t *m);
GEOAPICALL void mapnik_property_map_set_null(mapnik_property_map_t *m,
                                             const char *key);
GEOAPICALL void mapnik_property_map_set_bool(mapnik_property_map_t *m,
                                             const char *key, _Bool v);
GEOAPICALL void mapnik_property_map_set_uint64(mapnik_property_map_t *m,
                                               const char *key, uint64_t v);
GEOAPICALL void mapnik_property_map_set_int64(mapnik_property_map_t *m,
                                              const char *key, int64_t v);
GEOAPICALL void mapnik_property_map_set_double(mapnik_property_map_t *m,
                                               const char *key, double v);
GEOAPICALL void mapnik_property_map_set_string(mapnik_property_map_t *m,
                                               const char *key, const char *v);

GEOAPICALL mapnik_feature_t *feature_new(mapnik_geometry_t *geo,
                                         mapnik_identifier_t *id,
                                         mapnik_property_map_t *props);
GEOAPICALL void feature_free(mapnik_feature_t *m);

GEOAPICALL mapnik_feature_collection_t *feature_collection_new();
GEOAPICALL void feature_collection_free(mapnik_feature_collection_t *m);
GEOAPICALL void feature_collection_add_feature(mapnik_feature_collection_t *m,
                                               mapnik_feature_t *f);
GEOAPICALL void feature_collection_add_features(mapnik_feature_collection_t *m,
                                                mapnik_feature_t **f, int count);

GEOAPICALL mapnik_geometry_t *geometry_new(int type);
GEOAPICALL void geometry_free(mapnik_geometry_t *m);
GEOAPICALL int geometry_type(mapnik_geometry_t *m);

GEOAPICALL void add_line(mapnik_geometry_t *m, double x1, double y1, double x2,
                         double y2);
GEOAPICALL void add_point(mapnik_geometry_t *m, double x1, double y1);
GEOAPICALL void add_polygon(mapnik_geometry_t *m, double *points, int count);
GEOAPICALL void add_inner_linear_ring(mapnik_geometry_t *m, double *points,
                                      int count);
GEOAPICALL void add_geometry(mapnik_geometry_t *m,
                             const mapnik_geometry_t *geo);

#ifdef __cplusplus
}
#endif

#endif // MAPNIK_FEATURE_C_API_H