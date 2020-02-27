#include "feature_c_api.h"
#include "feature_impl.hh"

namespace {
mapnik::geometry::linear_ring<double> _build_linear_ring(double *points,
                                                         int count) {
  assert(count % 2 == 0);
  mapnik::geometry::linear_ring<double> ring;
  for (int i = 0; i < count / 2; i++) {
    double px = points[i * 2];
    double py = points[i * 2 + 1];
    ring.add_coord(px, py);
  }
  return std::move(ring);
}
} // namespace
#ifdef __cplusplus
extern "C" {
#endif

const int GEO_UNKNOWN = 0;
const int GEO_POINT = 1;
const int GEO_LINESTRING = 2;
const int GEO_POLYGON = 3;
const int GEO_MULTIPOINT = 4;
const int GEO_MULTILINESTRING = 5;
const int GEO_MULTIPOLYGON = 6;
const int GEO_COLLECTION = 7;

mapnik_identifier_t *mapnik_identifier_new_uint64(uint64_t id) {
  mapnik_identifier_t *m =
      new mapnik_identifier_t{flywave::nik::identifier{id}};
  return m;
}

mapnik_identifier_t *mapnik_identifier_new_int64(int64_t id) {
  mapnik_identifier_t *m =
      new mapnik_identifier_t{flywave::nik::identifier{id}};
  return m;
}

mapnik_identifier_t *mapnik_identifier_new_double(double id) {
  mapnik_identifier_t *m =
      new mapnik_identifier_t{flywave::nik::identifier{id}};
  return m;
}

mapnik_identifier_t *mapnik_identifier_new_string(const char *id) {
  mapnik_identifier_t *m =
      new mapnik_identifier_t{flywave::nik::identifier{std::string(id)}};
  return m;
}

void mapnik_identifier_free(mapnik_identifier_t *m) {
  if (m) {
    delete m;
  }
}

mapnik_property_value_t *mapnik_property_value_new() {
  mapnik_property_value_t *m = new mapnik_property_value_t{
      flywave::nik::value{flywave::nik::null_value}};
  return m;
}

mapnik_property_value_t *mapnik_property_value_new_bool(_Bool v) {
  mapnik_property_value_t *m =
      new mapnik_property_value_t{flywave::nik::value(bool(v))};
  return m;
}

mapnik_property_value_t *mapnik_property_value_new_uint64(uint64_t v) {
  mapnik_property_value_t *m =
      new mapnik_property_value_t{flywave::nik::value(v)};
  return m;
}

mapnik_property_value_t *mapnik_property_value_new_int64(int64_t v) {
  mapnik_property_value_t *m =
      new mapnik_property_value_t{flywave::nik::value(v)};
  return m;
}

mapnik_property_value_t *mapnik_property_value_new_double(double v) {
  mapnik_property_value_t *m =
      new mapnik_property_value_t{flywave::nik::value(v)};
  return m;
}

mapnik_property_value_t *mapnik_property_value_new_string(const char *v) {
  mapnik_property_value_t *m =
      new mapnik_property_value_t{flywave::nik::value{std::string(v)}};
  return m;
}

void mapnik_property_value_free(mapnik_property_value_t *m) {
  if (m) {
    delete m;
  }
}

mapnik_property_map_t *mapnik_property_map_new() {
  mapnik_property_map_t *m = new mapnik_property_map_t{};
  return m;
}

void mapnik_property_map_free(mapnik_property_map_t *m) {
  if (m) {
    delete m;
  }
}

void mapnik_property_map_set_null(mapnik_property_map_t *m, const char *key) {
  if (m) {
    m->map[key] = flywave::nik::null_value;
  }
}

void mapnik_property_map_set_bool(mapnik_property_map_t *m, const char *key,
                                  _Bool v) {
  if (m) {
    m->map[key] = flywave::nik::value(bool(v));
  }
}

void mapnik_property_map_set_uint64(mapnik_property_map_t *m, const char *key,
                                    uint64_t v) {
  if (m) {
    m->map[key] = flywave::nik::value(v);
  }
}

void mapnik_property_map_set_int64(mapnik_property_map_t *m, const char *key,
                                   int64_t v) {
  if (m) {
    m->map[key] = flywave::nik::value(v);
  }
}

void mapnik_property_map_set_double(mapnik_property_map_t *m, const char *key,
                                    double v) {
  if (m) {
    m->map[key] = flywave::nik::value(v);
  }
}

void mapnik_property_map_set_string(mapnik_property_map_t *m, const char *key,
                                    const char *v) {
  if (m) {
    m->map[key] = flywave::nik::value{std::string(v)};
  }
}

mapnik_feature_t *feature_new(mapnik_geometry_t *geo, mapnik_identifier_t *id,
                              mapnik_property_map_t *props) {
  mapnik_feature_t *m = new mapnik_feature_t{flywave::nik::feature<double>{
      geo->geo,
      props == NULL ? std::unordered_map<std::string, flywave::nik::value>{}
                    : props->map,
      id == NULL ? flywave::nik::identifier{} : id->id}};
  return m;
}

mapnik_feature_collection_t *feature_collection_new() {
  mapnik_feature_collection_t *m = new mapnik_feature_collection_t;
  return m;
}

void feature_collection_add_feature(mapnik_feature_collection_t *m,
                                    mapnik_feature_t *f) {
  if (m) {
    m->fc.emplace_back(f->f);
  }
}

void feature_collection_add_features(mapnik_feature_collection_t *m,
                                     mapnik_feature_t **f, int count) {
  if (m) {
    for (int i = 0; i < count; i++) {
      m->fc.emplace_back(f[i]->f);
    }
  }
}

void feature_collection_free(mapnik_feature_collection_t *m) {
  if (m) {
    delete m;
  }
}

void feature_free(mapnik_feature_t *m) {
  if (m) {
    delete m;
  }
}

mapnik_geometry_t *geometry_new(int type) {
  mapnik_geometry_t *m = new mapnik_geometry_t;
  m->mode = type;
  return m;
}

void geometry_free(mapnik_geometry_t *m) {
  if (m) {
    delete m;
  }
}

int geometry_type(mapnik_geometry_t *m) {
  if (m) {
    return m->mode;
  }
  return GEO_UNKNOWN;
}

void add_line(mapnik_geometry_t *m, double x1, double y1, double x2,
              double y2) {
  assert(m->mode == GEO_LINESTRING || m->mode == GEO_MULTILINESTRING);
  if (m->mode == GEO_LINESTRING) {
    mapnik::geometry::line_string<double> l;
    l.add_coord(x1, y1);
    l.add_coord(x2, y2);
    m->geo = l;
  } else {
    if (m->geo.template is<mapnik::geometry::geometry_empty>()) {
      m->geo = mapnik::geometry::multi_line_string<double>{};
    }
    mapnik::geometry::multi_line_string<double> &ml =
        m->geo.template get<mapnik::geometry::multi_line_string<double>>();
    mapnik::geometry::line_string<double> l;
    l.add_coord(x1, y1);
    l.add_coord(x2, y2);
    ml.emplace_back(l);
  }
}

void add_point(mapnik_geometry_t *m, double x1, double y1) {
  assert(m->mode == GEO_POINT || m->mode == GEO_MULTIPOINT);
  if (m->mode == GEO_POINT) {
    m->geo = mapnik::geometry::point<double>(x1, y1);
  } else {
    if (m->geo.template is<mapnik::geometry::multi_point<double>>()) {
      mapnik::geometry::multi_point<double> &line =
          m->geo.template get<mapnik::geometry::multi_point<double>>();
      line.emplace_back(mapnik::geometry::point<double>(x1, y1));
    }
  }
}

void add_polygon(mapnik_geometry_t *m, double *points, int count) {
  assert(m->mode == GEO_POLYGON || m->mode == GEO_MULTIPOLYGON);
  if (m->mode == GEO_POLYGON) {
    mapnik::geometry::polygon<double> poly;
    poly.exterior_ring = _build_linear_ring(points, count);
    m->geo = poly;
  } else {
    if (m->geo.template is<mapnik::geometry::geometry_empty>()) {
      m->geo = mapnik::geometry::multi_polygon<double>{};
    }
    mapnik::geometry::multi_polygon<double> &mpoly =
        m->geo.template get<mapnik::geometry::multi_polygon<double>>();
    mapnik::geometry::polygon<double> poly;
    poly.exterior_ring = _build_linear_ring(points, count);
    mpoly.emplace_back(poly);
  }
}

void add_inner_linear_ring(mapnik_geometry_t *m, double *points, int count) {
  assert(m->mode == GEO_POLYGON || m->mode == GEO_MULTIPOLYGON);
  if (m->mode == GEO_POLYGON) {
    mapnik::geometry::polygon<double> &poly =
        m->geo.template get<mapnik::geometry::polygon<double>>();
    poly.interior_rings.emplace_back(_build_linear_ring(points, count));
  } else {
    mapnik::geometry::multi_polygon<double> &mpoly =
        m->geo.template get<mapnik::geometry::multi_polygon<double>>();
    mpoly.end()->interior_rings.emplace_back(_build_linear_ring(points, count));
  }
}

void add_geometry(mapnik_geometry_t *m, const mapnik_geometry_t *geo) {
  assert(m->mode == GEO_COLLECTION);
  if (m->geo.template is<mapnik::geometry::geometry_empty>()) {
    m->geo = mapnik::geometry::geometry_collection<double>{};
  }
  mapnik::geometry::geometry_collection<double> geos =
      m->geo.template get<mapnik::geometry::geometry_collection<double>>();
  geos.emplace_back(geo->geo);
}

#ifdef __cplusplus
}
#endif
