#pragma once

#include <deque>
#include <vector>

#include <mapnik/featureset.hpp>

#include "feature.hh"
#include "geometry_datasource.hh"

namespace flywave {
namespace nik {

class geometry_featureset : public mapnik::Featureset {
public:
  using array_type =
      typename std::deque<typename geometry_datasource::item_type>;

  geometry_featureset(mapnik::box2d<double> const &box,
                      const feature_collection<double> &fs,
                      array_type &&index_array);

  mapnik::feature_ptr next() override;

private:
  mapnik::context_ptr ctx_;
  mutable unsigned int feature_id_;
  mutable mapnik::box2d<double> box_;
  const feature_collection<double> &fs_;
  const array_type index_array_;
  typename array_type::const_iterator index_itr_;
  typename array_type::const_iterator index_end_;
};
} // namespace nik
} // namespace flywave
