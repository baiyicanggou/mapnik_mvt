#include <mapnik/debug.hpp>
#include <mapnik/feature_factory.hpp>
#include <mapnik/image.hpp>
#include <mapnik/image_reader.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/raster.hpp>
#include <mapnik/util/variant.hpp>
#include <mapnik/view_transform.hpp>

#pragma GCC diagnostic push
#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <mapnik/warning_ignore.hpp>
#pragma GCC diagnostic pop

#include "raster_featureset.hh"

namespace flywave {
namespace nik {

using mapnik::feature_factory;
using mapnik::feature_ptr;
using mapnik::image_reader;
using mapnik::image_rgba8;
using mapnik::query;
using mapnik::raster;

template <typename LookupPolicy>
raster_featureset<LookupPolicy>::raster_featureset(
    LookupPolicy const &policy, mapnik::box2d<double> const &extent,
    query const &q)
    : policy_(policy), feature_id_(1),
      ctx_(std::make_shared<mapnik::context_type>()), extent_(extent),
      bbox_(q.get_bbox()), curIter_(policy_.begin()), endIter_(policy_.end()),
      filter_factor_(q.get_filter_factor()) {}

template <typename LookupPolicy>
raster_featureset<LookupPolicy>::~raster_featureset() {}

template <typename LookupPolicy>
feature_ptr raster_featureset<LookupPolicy>::next() {
  if (curIter_ != endIter_) {
    feature_ptr feature(feature_factory::create(ctx_, feature_id_++));

    try {
      int image_width = policy_.img_width(curIter_->width());
      int image_height = policy_.img_height(curIter_->height());

      if (image_width > 0 && image_height > 0) {
        mapnik::view_transform t(image_width, image_height, extent_, 0, 0);
        mapnik::box2d<double> intersect = bbox_.intersect(curIter_->envelope());
        mapnik::box2d<double> ext = t.forward(intersect);
        mapnik::box2d<double> rem = policy_.transform(ext);

        int x_off = static_cast<int>(std::floor(ext.minx()));
        int y_off = static_cast<int>(std::floor(ext.miny()));
        int end_x = static_cast<int>(std::ceil(ext.maxx()));
        int end_y = static_cast<int>(std::ceil(ext.maxy()));

        if (x_off >= image_width)
          x_off = image_width - 1;
        if (y_off >= image_height)
          y_off = image_height - 1;
        if (x_off < 0)
          x_off = 0;
        if (y_off < 0)
          y_off = 0;
        if (end_x > image_width)
          end_x = image_width;
        if (end_y > image_height)
          end_y = image_height;

        int width = end_x - x_off;
        int height = end_y - y_off;
        if (width < 1)
          width = 1;
        if (height < 1)
          height = 1;

        mapnik::box2d<double> feature_raster_extent(
            rem.minx() + x_off, rem.miny() + y_off, rem.maxx() + x_off + width,
            rem.maxy() + y_off + height);
        feature_raster_extent = t.backward(feature_raster_extent);
        mapnik::image_any data = curIter_->read(x_off, y_off, width, height);
        mapnik::raster_ptr raster = std::make_shared<mapnik::raster>(
            feature_raster_extent, intersect, std::move(data), filter_factor_);
        feature->set_raster(raster);
      }
    } catch (mapnik::image_reader_exception const &ex) {

    } catch (std::exception const &ex) {
    } catch (...) {
    }

    ++curIter_;
    return feature;
  }
  return feature_ptr();
}

template class raster_featureset<single_file_policy>;
template class raster_featureset<tiled_file_policy>;
template class raster_featureset<tiled_multi_file_policy>;
} // namespace nik
} // namespace flywave
