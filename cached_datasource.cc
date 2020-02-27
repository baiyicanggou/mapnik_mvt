#include "cached_datasource.hh"

namespace flywave {
namespace nik {

cached_datasource::cached_datasource(mapnik::datasource_ptr ds)
    : virtual_datasource("cache"), p_datasource_(std::move(ds)) {
  assert(p_datasource_);
}

mapnik::datasource::datasource_t cached_datasource::type() const {
  return p_datasource_->type();
}

boost::optional<mapnik::datasource_geometry_t>
cached_datasource::get_geometry_type() const {
  return p_datasource_->get_geometry_type();
}

mapnik::featureset_ptr
cached_datasource::features(mapnik::query const &q) const {
  const auto &q_bbox = q.get_bbox();
  if (q_bbox != cached_bbox_) {
    cached_bbox_ = q_bbox;
    cached_features_ =
        std::make_shared<cached_featureset>(p_datasource_->features(q));
  }
  return mapnik::featureset_ptr(cached_features_);
}

mapnik::featureset_ptr
cached_datasource::features_at_point(mapnik::coord2d const &pt,
                                     double tol) const {
  return p_datasource_->features_at_point(pt, tol);
}

mapnik::box2d<double> cached_datasource::envelope() const {
  return p_datasource_->envelope();
}

mapnik::layer_descriptor cached_datasource::get_descriptor() const {
  return p_datasource_->get_descriptor();
}
} // namespace nik
} // namespace flywave
