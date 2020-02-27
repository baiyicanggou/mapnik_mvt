#include "geometry_datasource.hh"
#include "geometry_featureset.hh"

namespace flywave {
namespace nik {

struct mapnik_type_visitor {

  int operator()(mapnik::geometry::point<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::Point);
  }

  int operator()(mapnik::geometry::multi_point<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::Point);
  }

  int operator()(mapnik::geometry::line_string<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::LineString);
  }

  int operator()(mapnik::geometry::multi_line_string<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::LineString);
  }

  int operator()(mapnik::geometry::polygon<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::Polygon);
  }

  int operator()(mapnik::geometry::multi_polygon<double> const &) const {
    return static_cast<int>(mapnik::datasource_geometry_t::Polygon);
  }

  template <typename C> int operator()(C const &) const { return 0; }
};

geometry_datasource::geometry_datasource(feature_collection<double> features)
    : virtual_datasource("vector"), features_(features), cached_features_(),
      tree_(nullptr), desc_("vector", "utf-8") {
  init();
}

mapnik::datasource::datasource_t geometry_datasource::type() const {
  return datasource::Vector;
}

boost::optional<mapnik::datasource_geometry_t>
geometry_datasource::get_geometry_type() const {
  return geometry_type_;
}

mapnik::featureset_ptr
geometry_datasource::features(mapnik::query const &q) const {
  const auto &q_bbox = q.get_bbox();
  if (extent_.intersects(q_bbox)) {
    if (cached_extent_ != q_bbox) {
      cached_extent_ = q_bbox;

      typename geometry_featureset::array_type index_array;
      if (tree_) {
        tree_->query(boost::geometry::index::intersects(q_bbox),
                     std::back_inserter(index_array));
        cached_features_ = std::make_shared<geometry_featureset>(
            q_bbox, features_, std::move(index_array));
      }
    }
    return mapnik::featureset_ptr(cached_features_);
  }
  return mapnik::make_invalid_featureset();
}

mapnik::featureset_ptr
geometry_datasource::features_at_point(mapnik::coord2d const &pt,
                                       double tol) const {
  return mapnik::featureset_ptr();
}

mapnik::box2d<double> geometry_datasource::envelope() const { return extent_; }

void geometry_datasource::init() {
  extent_.init(-180, -90, 180, 90);

  using values_container = std::vector<std::pair<box_type, std::size_t>>;
  values_container values;
  values.reserve(features_.size());
  std::size_t geometry_index = 0;

  int multi_type = 0;

  for (auto const &geom : features_) {
    mapnik::box2d<double> box = mapnik::geometry::envelope(geom.geometry);
    if (box.valid()) {
      extent_.expand_to_include(box);
      values.emplace_back(box, geometry_index);
    }

    int type =
        mapnik::util::apply_visitor(mapnik_type_visitor(), geom.geometry);
    if (type > 0) {
      if (multi_type > 0 && multi_type != type) {
        geometry_type_ = mapnik::datasource_geometry_t::Collection;
      } else {
        geometry_type_ = static_cast<mapnik::datasource_geometry_t>(type);
      }
      multi_type = type;
    }
    geometry_index++;
  }

  tree_ = std::make_unique<spatial_index_type>(values);
}

mapnik::layer_descriptor geometry_datasource::get_descriptor() const {
  return desc_;
}

} // namespace nik
} // namespace flywave
