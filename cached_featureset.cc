#include "cached_featureset.hh"
#include <cassert>

namespace flywave {
namespace nik {

cached_featureset::cached_featureset(mapnik::featureset_ptr fs)
    : fs_(std::move(fs)), cached_(false) {
  assert(fs_);
}

mapnik::feature_ptr cached_featureset::next() {
  if (cached_) {
    if (iter_ == cached_features_.end()) {
      iter_ = cached_features_.begin();
      return mapnik::feature_ptr();
    }
    return mapnik::feature_ptr(*iter_++);
  }
  auto f_ptr = fs_->next();
  if (f_ptr) {
    cached_features_.push_back(f_ptr);
  } else {
    cached_ = true;
    iter_ = cached_features_.begin();
  }
  return f_ptr;
}
} // namespace nik
} // namespace flywave
