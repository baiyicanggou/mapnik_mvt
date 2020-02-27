#pragma once

#include "grid.hh"
#include "source.hh"
#include "tile.hh"

namespace flywave {
namespace nik {

struct tiler_options {
  unsigned per_load_tile_count = 16;
};

class tiler {
public:
  tiler(std::shared_ptr<source> source, std::shared_ptr<grid> g,
        std::unique_ptr<tiler_options> options)
      : _source(std::move(source)), _grid(std::move(g)),
        _bounds(_grid->get_extent()), _options(std::move(options)) {}

  tiler(tiler &&other) = default;
  tiler &operator=(tiler &&other) = default;

  virtual ~tiler() {}

  virtual std::unique_ptr<mapnik_tile>
  create_tile(const tile_id &coord) const = 0;

  inline unsigned max_zoom() const {
    return _grid->zoom_for_resolution(resolution());
  }

  inline tile_id lower_left_tile(unsigned int zoom) const {
    return _grid->crs_to_tile_min(
        mapnik::coord<double, 2>{_bounds.minx(), _bounds.miny()}, zoom);
  }

  inline tile_id upper_right_tile(unsigned int zoom) const {
    return _grid->crs_to_tile_max(
        mapnik::coord<double, 2>{_bounds.maxx(), _bounds.maxy()}, zoom);
  }

  inline tile_bounds tile_bounds_for_zoom(unsigned int zoom) const {
    tile_id ll = _grid->crs_to_tile_min(
                mapnik::coord<double, 2>{_bounds.minx(), _bounds.miny()}, zoom),
            ur = _grid->crs_to_tile_max(
                mapnik::coord<double, 2>{_bounds.maxx(), _bounds.maxy()}, zoom);
    return tile_bounds{{ll.x, ll.y}, {ur.x, ur.y}};
  }

  inline double resolution() const { return _resolution; }

  inline const nik::grid *grid() const { return _grid.get(); };

  inline const mapnik::box2d<double> &bounds() const {
    return const_cast<const mapnik::box2d<double> &>(_bounds);
  }

protected:
  virtual tile_bounds compute_box(const tile_ext_id &coord) const;

  std::shared_ptr<nik::grid> _grid;

  std::shared_ptr<source> _source;

  std::unique_ptr<tiler_options> _options;

  mapnik::box2d<double> _bounds;

  double _resolution;
};
} // namespace nik
} // namespace flywave
