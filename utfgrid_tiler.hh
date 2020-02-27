#pragma once

#include "grid.hh"
#include "mapnik_tiler.hh"
#include "source.hh"
namespace flywave {
namespace nik {

struct utfgrid_tiler_options : public mapnik_tiler_options {
  std::string utfgrid_key;
};

class utfgrid_tiler : public mapnik_tiler {
public:
  utfgrid_tiler(std::shared_ptr<nik::source> source,
                std::shared_ptr<nik::grid> g,
                std::unique_ptr<utfgrid_tiler_options> options)
      : mapnik_tiler(source, g, std::move(options)) {}

  utfgrid_tiler(std::shared_ptr<nik::source> source,
                std::shared_ptr<nik::grid> g)
      : utfgrid_tiler(source, g, std::make_unique<utfgrid_tiler_options>()) {}

  utfgrid_tiler &operator=(utfgrid_tiler &&other) {
    mapnik_tiler::operator=(std::move(other));
    return *this;
  }

  virtual std::unique_ptr<mapnik_tile>
  create_tile(const tile_id &coord) const override {
    return create_mapnik_tile(tile_ext_id{coord});
  }

  inline utfgrid_tiler_options *options() const {
    return reinterpret_cast<utfgrid_tiler_options *>(_options.get());
  }

protected:
  void render(mapnik_ext_tile &etile, mapnik::Map &map) const override;
};

} // namespace nik
} // namespace flywave
