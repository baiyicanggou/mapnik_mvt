#pragma once

#include <mapnik/datasource.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/geometry_adapters.hpp>

#include <boost/geometry/index/rtree.hpp>

#include "feature.hh"
#include "virtual_datasource.hh"

namespace flywave {
namespace nik {

class geometry_datasource : public virtual_datasource {
public:
  using box_type = mapnik::box2d<double>;
  using item_type = std::pair<box_type, std::size_t>;
  using linear_type = boost::geometry::index::linear<16, 4>;
  using spatial_index_type =
      boost::geometry::index::rtree<item_type, linear_type>;

  geometry_datasource(feature_collection<double> ds);

  datasource_t type() const override;
  boost::optional<mapnik::datasource_geometry_t>
  get_geometry_type() const override;

  mapnik::featureset_ptr features(mapnik::query const &q) const override;
  mapnik::featureset_ptr features_at_point(mapnik::coord2d const &pt,
                                           double tol = 0) const override;

  mapnik::box2d<double> envelope() const override;
  mapnik::layer_descriptor get_descriptor() const override;

private:
  void init();

  mutable mapnik::box2d<double> extent_;
  mutable mapnik::box2d<double> cached_extent_;
  mutable mapnik::featureset_ptr cached_features_{nullptr};
  mapnik::layer_descriptor desc_;
  feature_collection<double> features_;
  std::unique_ptr<spatial_index_type> tree_;
  mapnik::datasource_geometry_t geometry_type_;
};

} // namespace nik
} // namespace flywave
