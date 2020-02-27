#pragma once

#include <mapnik/coord.hpp>
#include <mapnik/datasource.hpp>
#include <mapnik/feature.hpp>
#include <mapnik/feature_layer_desc.hpp>
#include <mapnik/params.hpp>
#include <mapnik/query.hpp>

#include <boost/optional.hpp>
#include <memory>

#include <string>
#include <unordered_map>
#include <vector>

#include "virtual_datasource.hh"

namespace flywave {
namespace nik {

class raster_data;

typedef std::shared_ptr<raster_data> raster_data_ptr;
typedef std::vector<raster_data_ptr> raster_tiled_data;

class raster_datasource : public virtual_datasource {
public:
  raster_datasource(raster_data_ptr ds, unsigned tile_size);
  raster_datasource(raster_tiled_data datas, mapnik::box2d<double> extent,
                    unsigned row, unsigned col, unsigned tile_size);
  virtual ~raster_datasource();

  datasource::datasource_t type() const;

  mapnik::featureset_ptr features(const mapnik::query &q) const;
  mapnik::featureset_ptr features_at_point(mapnik::coord2d const &pt,
                                           double tol = 0) const;
  mapnik::box2d<double> envelope() const;
  boost::optional<mapnik::datasource_geometry_t> get_geometry_type() const;
  mapnik::layer_descriptor get_descriptor() const;

private:
  mapnik::layer_descriptor desc_;
  raster_data_ptr data_;
  raster_tiled_data datas_;
  mapnik::box2d<double> extent_;
  bool extent_initialized_;
  bool multi_tiles_;
  unsigned tile_size_;
  unsigned width_;
  unsigned height_;
  unsigned tile_stride_;
};
} // namespace nik
} // namespace flywave
