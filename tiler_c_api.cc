#include "tiler_c_api.h"

#include "datasource_impl.hh"
#include "mapnik_grid.hh"
#include "mapnik_impl.hh"
#include "mapnik_source.hh"
#include "mapnik_tiler.hh"
#include "mvt_tiler.hh"
#include "tiler_iterator.hh"
#include "utfgrid_tiler.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _tiler_source_options_t {
  flywave::nik::map_options opts;
};

tiler_source_options_t *tiler_source_options_new() {
  tiler_source_options_t *m = new tiler_source_options_t{{}};
  return m;
}

void tiler_source_options_free(tiler_source_options_t *m) {
  if (m) {
    delete m;
  }
}

void tiler_source_options_add(tiler_source_options_t *m, const char *name,
                              mapnik_map_t *map) {
  if (m) {
    m->opts.emplace_back(flywave::nik::map_option{name, map->m});
  }
}

struct _tiler_source_t {
  std::shared_ptr<flywave::nik::mapnik_source> src;
};

tiler_source_t *tiler_source_new(tiler_source_options_t *opts) {
  tiler_source_t *m = new tiler_source_t{
      std::make_shared<flywave::nik::mapnik_source>(opts->opts)};
  return m;
}

void tiler_source_free(tiler_source_t *m) {
  if (m) {
    delete m;
  }
}

void tiler_source_add_datasource(tiler_source_t *m, const char *name,
                                 mapnik_datasource_t *ds) {
  if (m) {
    m->src->add_datasource(name, ds->ptr);
  }
}

struct _tiler_grid_t {
  std::shared_ptr<flywave::nik::grid> grid;
};

tiler_grid_t *tiler_global_geodetic_grid(unsigned int tileSize) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::global_geodetic>(tileSize)};
  return m;
}

tiler_grid_t *tiler_global_mercator_grid(unsigned int tileSize) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::global_mercator>(tileSize)};
  return m;
}

tiler_grid_t *tiler_global_geodetic_local_grid(unsigned int tileSize,
                                               double *box) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::global_geodetic>(mapnik::box2d<double>({box[0], box[1]}, {box[2], box[3]}),tileSize)};
  return m;
}

tiler_grid_t *tiler_global_mercator_local_grid(unsigned int tileSize,
                                               double *box) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::global_mercator>(mapnik::box2d<double>({box[0], box[1]}, {box[2], box[3]}),tileSize)};
  return m;
}

tiler_grid_t *tiler_geodetic_grid(unsigned int tileSize, double *box) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::mapnik_geodetic_grid>(
          tileSize, mapnik::box2d<double>({box[0], box[1]}, {box[2], box[3]})),
  };
  return m;
}

tiler_grid_t *tiler_mercator_grid(unsigned int tileSize, double *box) {
  tiler_grid_t *m = new tiler_grid_t{
      std::make_shared<flywave::nik::mapnik_mercator_grid>(
          tileSize, mapnik::box2d<double>({box[0], box[1]}, {box[2], box[3]})),
  };
  return m;
}

void tiler_grid_free(tiler_grid_t *m) {
  if (m) {
    delete m;
  }
}

struct _mapnik_tiler_options_t {
  std::unique_ptr<flywave::nik::mapnik_tiler_options> options;
};

mapnik_tiler_options_t *mapnik_tiler_options_new(const char *style) {
  mapnik_tiler_options_t *m = new mapnik_tiler_options_t{
      std::make_unique<flywave::nik::mapnik_tiler_options>()};
  m->options->style_name = style;
  return m;
}

void mapnik_tiler_options_add_layer(mapnik_tiler_options_t *m,
                                    const char *name) {
  if (m) {
    if (m->options->layers == nullptr) {
      m->options->layers = std::make_unique<std::set<std::string>>();
    }
    m->options->layers->emplace(name);
  }
}

void mapnik_tiler_options_free(mapnik_tiler_options_t *m) {
  if (m) {
    delete m;
  }
}

struct _mapnik_tiler_t {
  std::unique_ptr<flywave::nik::tiler> t;
};

mapnik_tiler_t *mapnik_tiler_new(tiler_source_t *source, tiler_grid_t *grid,
                                 mapnik_tiler_options_t *opts) {
  mapnik_tiler_t *m =
      new mapnik_tiler_t{std::make_unique<flywave::nik::mapnik_tiler>(
          source->src, grid->grid, std::move(opts->options))};
  return m;
}

void mapnik_tiler_free(mapnik_tiler_t *m) {
  if (m) {
    delete m;
  }
}

extern void writeTileFunc(void *ctx, _mapnik_tile_t *t);

void mapnik_tiler_render_select(mapnik_tiler_t *m, uint16_t *zooms, int count,
                                void *data) {
  if (m) {
    std::vector<uint16_t> select;
    select.resize(count);
    for (int i = 0; i < count; i++) {
      select[i] = zooms[i];
    }
    flywave::nik::tiler_iterator iter{*m->t, select};
    for (++iter; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      _mapnik_tile_t *m = new _mapnik_tile_t{std::move(*tile.get())};
      writeTileFunc(data, m);
    }
  }
}

void mapnik_tiler_render(mapnik_tiler_t *m, unsigned int startZoom,
                         unsigned int endZoom, void *data) {
  if (m) {
    flywave::nik::tiler_iterator iter{*m->t, startZoom, endZoom};
    for (; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      _mapnik_tile_t *m = new _mapnik_tile_t{std::move(*tile.get())};
      writeTileFunc(data, m);
    }
  }
}

struct _mvt_tiler_options_t {
  std::unique_ptr<flywave::nik::mvt_tiler_options> options;
};

struct _mvt_tiler_t {
  std::unique_ptr<flywave::nik::tiler> t;
};

mvt_tiler_options_t *mvt_tiler_options_new(const char *style) {
  mvt_tiler_options_t *m = new mvt_tiler_options_t{
      std::make_unique<flywave::nik::mvt_tiler_options>()};
  m->options->style_name = style;
  return m;
}

void mvt_tiler_options_add_layer(mvt_tiler_options_t *m, const char *name) {
  if (m) {
    if (m->options->layers == nullptr) {
      m->options->layers = std::make_unique<std::set<std::string>>();
    }
    m->options->layers->emplace(name);
  }
}
void mvt_tiler_options_free(mvt_tiler_options_t *m) {
  if (m) {
    delete m;
  }
}

// mvt tiler
mvt_tiler_t *mvt_tiler_new(tiler_source_t *source, tiler_grid_t *grid,
                           mvt_tiler_options_t *opts) {
  mvt_tiler_t *m = new mvt_tiler_t{std::make_unique<flywave::nik::mvt_tiler>(
      source->src, grid->grid, std::move(opts->options))};
  return m;
}
void mvt_tiler_free(mvt_tiler_t *m) {
  if (m) {
    delete m;
  }
}
extern void writeMvtTileFunc(void *ctx, _mvt_tile_t *t);

void mvt_tiler_render_select(mvt_tiler_t *m, uint16_t *zooms, int count,
                             void *data) {
  if (m) {
    std::vector<uint16_t> select;
    select.resize(count);
    for (int i = 0; i < count; i++) {
      select[i] = zooms[i];
    }
    flywave::nik::tiler_iterator iter{*m->t, select};
    for (++iter; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      auto ptr = static_cast<flywave::nik::mvt_tile *>(tile.get());
        _mvt_tile_t *m = new _mvt_tile_t{std::move(*ptr)};
      writeMvtTileFunc(data, m);
     }
  }
}

void mvt_tiler_render(mvt_tiler_t *m, unsigned int startZoom,
                      unsigned int endZoom, void *data) {
  if (m) {
    flywave::nik::tiler_iterator iter{*m->t, startZoom, endZoom};
    for (; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      _mvt_tile_t *m = new _mvt_tile_t{std::move(*tile.get())};
      writeMvtTileFunc(data, m);
     }
  }
}

struct _utfgrid_tiler_options_t {
  std::unique_ptr<flywave::nik::utfgrid_tiler_options> options;
};

struct _utfgrid_tiler_t {
  std::unique_ptr<flywave::nik::tiler> t;
};

utfgrid_tiler_options_t *utfgrid_tiler_options_new(const char *style) {
  utfgrid_tiler_options_t *m = new utfgrid_tiler_options_t{
      std::make_unique<flywave::nik::utfgrid_tiler_options>()};
  m->options->style_name = style;
  return m;
}

void utfgrid_tiler_options_add_layer(utfgrid_tiler_options_t *m,
                                     const char *name) {
  if (m) {
    if (m->options->layers == nullptr) {
      m->options->layers = std::make_unique<std::set<std::string>>();
    }
    m->options->layers->emplace(name);
  }
}
void utfgrid_tiler_options_free(utfgrid_tiler_options_t *m) {
  if (m) {
    delete m;
  }
}

// utfgrid tiler
utfgrid_tiler_t *utfgrid_tiler_new(tiler_source_t *source, tiler_grid_t *grid,
                                   utfgrid_tiler_options_t *opts) {
  utfgrid_tiler_t *m =
      new utfgrid_tiler_t{std::make_unique<flywave::nik::utfgrid_tiler>(
          source->src, grid->grid, std::move(opts->options))};
  return m;
}
void utfgrid_tiler_free(utfgrid_tiler_t *m) {
  if (m) {
    delete m;
  }
}
extern void writeUtfgridTileFunc(void *ctx, _utfgrid_tile_t *t);

void utfgrid_tiler_render_select(utfgrid_tiler_t *m, uint16_t *zooms, int count,
                                 void *data) {
  if (m) {
    std::vector<uint16_t> select;
    select.resize(count);
    for (int i = 0; i < count; i++) {
      select[i] = zooms[i];
    }
    flywave::nik::tiler_iterator iter{*m->t, select};
    for (++iter; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      _utfgrid_tile_t *m = new _utfgrid_tile_t{std::move(*tile.get())};
      writeUtfgridTileFunc(data, m);
     }
  }
}

void utfgrid_tiler_render(utfgrid_tiler_t *m, unsigned int startZoom,
                          unsigned int endZoom, void *data) {
  if (m) {
    flywave::nik::tiler_iterator iter{*m->t, startZoom, endZoom};
    for (; !iter.exhausted(); ++iter) {
      auto tile = *iter;
      _utfgrid_tile_t *m = new _utfgrid_tile_t{std::move(*tile.get())};
      writeUtfgridTileFunc(data, m);
     }
  }
}

#ifdef __cplusplus
}
#endif
