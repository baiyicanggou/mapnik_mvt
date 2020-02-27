#pragma once

#include <set>

#include "grid.hh"
#include "mapnik_source.hh"
#include "mapnik_tile.hh"
#include "source.hh"
#include "tiler.hh"

#include <mapnik/map.hpp>

namespace flywave {
namespace nik {

struct mapnik_tiler_options : public tiler_options {
  std::unique_ptr<std::set<std::string>> layers;
  std::string style_name;
};

class mapnik_tiler : public tiler {
public:
  mapnik_tiler(std::shared_ptr<nik::source> source,
               std::shared_ptr<nik::grid> g,
               std::unique_ptr<mapnik_tiler_options> options)
      : tiler(std::move(source), std::move(g), std::move(options)) {
    this->source()->set_current_style(this->options()->style_name);
  }
  mapnik_tiler(mapnik_tiler &&other) = default;

  mapnik_tiler &operator=(mapnik_tiler &&other) = default;

  virtual ~mapnik_tiler() {}

  inline mapnik_tiler_options *options() const {
    return reinterpret_cast<mapnik_tiler_options *>(_options.get());
  }

  inline mapnik_source *source() const {
    return reinterpret_cast<mapnik_source *>(_source.get());
  }

  virtual std::unique_ptr<nik::mapnik_tile>
  create_tile(const nik::tile_id &coord) const {
    return create_mapnik_tile(nik::tile_ext_id{coord});
  }

  inline const nik::grid *grid() const { return _grid.get(); }

protected:
  virtual std::unique_ptr<nik::mapnik_tile>
  create_mapnik_tile(const nik::tile_ext_id &coord) const;

  virtual void render(mapnik_ext_tile &etile, mapnik::Map &map) const;
};
} // namespace nik
} // namespace flywave
