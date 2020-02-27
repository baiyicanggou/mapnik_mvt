#pragma once

#include "filter_table.hh"
#include "grid.hh"
#include "mapnik_tiler.hh"
#include "source.hh"

namespace flywave {
namespace nik {

struct mvt_tiler_options : public mapnik_tiler_options {
  std::shared_ptr<const nik::filter_table> filter_table;
};

class mvt_tiler : public mapnik_tiler {
public:
  mvt_tiler(std::shared_ptr<nik::source> src, std::shared_ptr<nik::grid> g,
            std::unique_ptr<mvt_tiler_options> opts)
      : mapnik_tiler(src, g, std::move(opts)) {}

  mvt_tiler &operator=(mvt_tiler &&other) {
    mapnik_tiler::operator=(std::move(other));
    return *this;
  }

  virtual std::unique_ptr<mapnik_tile>
  create_tile(const tile_id &coord) const override {
    return create_mapnik_tile(tile_ext_id{coord});
  }

  inline mvt_tiler_options *options() const {
    return reinterpret_cast<mvt_tiler_options *>(_options.get());
  }

protected:
  void render(mapnik_ext_tile &etile, mapnik::Map &map) const override;
};
} // namespace nik
} // namespace flywave
