#include "tilerender_c_api.h"

#include "make_image_tile.hh"
#include "mapnik_impl.hh"
#include "tile.hh"

#ifdef __cplusplus
extern "C" {
#endif

mapnik_tile_t *mapnik_tile(uint32_t x, uint32_t y, uint32_t z, uint32_t width,
                           uint32_t height) {
  auto extid =
      flywave::nik::tile_ext_id(flywave::nik::tile_id(x, y, z), width, height);
  _mapnik_tile_t *m = new _mapnik_tile_t{flywave::nik::mapnik_tile(extid)};
  return m;
}

void mapnik_tile_free(mapnik_tile_t *m) {
  if (m) {
    delete m;
  }
}

int mapnik_tile_data_count(mapnik_tile_t *m) {
  if (m) {
    return int(m->data.tiles.size());
  }
  return 0;
}

const uint8_t *mapnik_tile_get_data(mapnik_tile_t *m, int i, int *si,
                                    uint32_t *x, uint32_t *y, uint32_t *z) {
  if (m && i < m->data.tiles.size()) {
    flywave::nik::tile_data &d = m->data.tiles[i];
    *si = int(d.data.size());
    *x = d.id.x;
    *y = d.id.y;
    *z = d.id.z;
    return reinterpret_cast<const uint8_t *>(d.data.c_str());
  }
  *si = *x = *y = *z = 0;
  return NULL;
}

mvt_tile_t *mvt_tile(uint32_t x, uint32_t y, uint32_t z, uint32_t width,
                     uint32_t height) {
  auto extid =
      flywave::nik::tile_ext_id(flywave::nik::tile_id(x, y, z), width, height);
  _mvt_tile_t *m = new _mvt_tile_t{flywave::nik::mvt_tile(extid)};
  return m;
}

void mvt_tile_free(mvt_tile_t *m) {
  if (m) {
    delete m;
  }
}
int mvt_tile_data_count(mvt_tile_t *m) {
  if (m) {
    return int(m->data.tiles.size());
  }
  return 0;
}

const uint8_t *mvt_tile_get_data(mvt_tile_t *m, int i, int *si, uint32_t *x,
                                 uint32_t *y, uint32_t *z) {
  if (m && i < m->data.tiles.size()) {
    flywave::nik::tile_data &d = m->data.tiles[i];
    *si = int(d.data.size());
    *x = d.id.x;
    *y = d.id.y;
    *z = d.id.z;
    return reinterpret_cast<const uint8_t *>(d.data.c_str());
  }
  *si = *x = *y = *z = 0;
  return NULL;
}

utfgrid_tile_t *utfgrid_tile(uint32_t x, uint32_t y, uint32_t z, uint32_t width,
                             uint32_t height) {
  auto extid =
      flywave::nik::tile_ext_id(flywave::nik::tile_id(x, y, z), width, height);
  _utfgrid_tile_t *m = new _utfgrid_tile_t{flywave::nik::mapnik_tile(extid)};
  return m;
}

void utfgrid_tile_free(utfgrid_tile_t *m) {
  if (m) {
    delete m;
  }
}
int utfgrid_tile_data_count(utfgrid_tile_t *m) {
  if (m) {
    return int(m->data.tiles.size());
  }
  return 0;
}

const uint8_t *utfgrid_tile_get_data(utfgrid_tile_t *m, int i, int *si,
                                     uint32_t *x, uint32_t *y, uint32_t *z) {
  if (m && i < m->data.tiles.size()) {
    flywave::nik::tile_data &d = m->data.tiles[i];
    *si = int(d.data.size());
    *x = d.id.x;
    *y = d.id.y;
    *z = d.id.z;
    return reinterpret_cast<const uint8_t *>(d.data.c_str());
  }
  *si = *x = *y = *z = 0;
  return NULL;
}

#ifdef __cplusplus
}
#endif
