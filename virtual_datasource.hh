#pragma once

#include <mapnik/datasource.hpp>

#include "cached_featureset.hh"

namespace flywave {
namespace nik {

class virtual_datasource : public mapnik::datasource {
public:
  virtual_datasource(const std::string &source_name)
      : datasource(mapnik::parameters()), source_name_(source_name),
        desc_(mapnik::layer_descriptor{"", ""}) {}

  const std::string &source_name() { return source_name_; }

  datasource_t type() const override { return mapnik::datasource::Vector; }
  boost::optional<mapnik::datasource_geometry_t>
  get_geometry_type() const override {
    return mapnik::datasource_geometry_t::Unknown;
  }

  mapnik::featureset_ptr features(mapnik::query const &q) const override {
    return nullptr;
  }
  mapnik::featureset_ptr features_at_point(mapnik::coord2d const &pt,
                                           double tol = 0) const override {

    return nullptr;
  }

  mapnik::box2d<double> envelope() const override { return extent_; }

  mapnik::layer_descriptor get_descriptor() const override { return desc_; }

private:
  mutable mapnik::box2d<double> extent_;

  std::string source_name_;
  const mapnik::datasource_ptr p_datasource_;
  mapnik::layer_descriptor desc_;
};
} // namespace nik
} // namespace flywave
