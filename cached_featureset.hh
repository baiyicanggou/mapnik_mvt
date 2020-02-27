#pragma once

#include <vector>

#include <mapnik/featureset.hpp>

namespace flywave {
namespace nik {

class cached_featureset : public mapnik::Featureset {
public:
  cached_featureset(mapnik::featureset_ptr fs);

  mapnik::feature_ptr next() override;

private:
  using cached_features_t = std::vector<mapnik::feature_ptr>;
  cached_features_t cached_features_;
  const mapnik::featureset_ptr fs_;
  cached_features_t::iterator iter_;
  bool cached_{false};
};
} // namespace nik
} // namespace flywave
