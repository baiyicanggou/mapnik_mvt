#ifndef MAPNIK_FEATURE_IMPL_H
#define MAPNIK_FEATURE_IMPL_H

#include "feature.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _mapnik_identifier_t {
  flywave::nik::identifier id;
};

struct _mapnik_property_value_t {
  flywave::nik::value val;
};

struct _mapnik_property_map_t {
  flywave::nik::property_map map;
};

struct _mapnik_feature_t {
  flywave::nik::feature<double> f;
};

struct _mapnik_feature_collection_t {
  flywave::nik::feature_collection<double> fc;
};

struct _mapnik_geometry_t {
  mapnik::geometry::geometry<double> geo;
  int mode;
};

#ifdef __cplusplus
}
#endif

#endif