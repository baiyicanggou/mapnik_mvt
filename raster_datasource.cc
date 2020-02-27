#include <mapnik/boolean.hpp>
#include <mapnik/debug.hpp>
#include <mapnik/image_reader.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/util/fs.hpp>
#include <mapnik/view_transform.hpp>

#include "raster_data.hh"
#include "raster_datasource.hh"
#include "raster_featureset.hh"
#include "raster_tiled_reader.hh"

namespace flywave {
namespace nik {

using mapnik::coord2d;
using mapnik::datasource;
using mapnik::datasource_exception;
using mapnik::featureset_ptr;
using mapnik::image_reader;
using mapnik::layer_descriptor;
using mapnik::parameters;
using mapnik::query;

raster_datasource::raster_datasource(raster_data_ptr ds, unsigned tile_size)
    : virtual_datasource("raster"), desc_("raster", "utf-8"),
      extent_initialized_(true), data_(ds), tile_size_(tile_size),
      extent_(data_->envelope()), width_(data_->width()),
      height_(data_->height()), tile_stride_(1) {}

raster_datasource::raster_datasource(raster_tiled_data datas,
                                     mapnik::box2d<double> extent, unsigned row,
                                     unsigned col, unsigned tile_size)
    : virtual_datasource("raster"), desc_("raster", "utf-8"),
      extent_initialized_(false), datas_(datas), tile_size_(tile_size),
      multi_tiles_(true), extent_(extent), tile_stride_(col) {
  width_ = col * tile_size_;
  height_ = row * tile_size_;
  extent_initialized_ = true;
}

raster_datasource::~raster_datasource() {}

mapnik::datasource::datasource_t raster_datasource::type() const {
  return datasource::Raster;
}

mapnik::box2d<double> raster_datasource::envelope() const { return extent_; }

boost::optional<mapnik::datasource_geometry_t>
raster_datasource::get_geometry_type() const {
  return boost::optional<mapnik::datasource_geometry_t>();
}

layer_descriptor raster_datasource::get_descriptor() const { return desc_; }

featureset_ptr raster_datasource::features(query const &q) const {
  mapnik::view_transform t(width_, height_, extent_, 0, 0);
  mapnik::box2d<double> intersect = extent_.intersect(q.get_bbox());
  mapnik::box2d<double> ext = t.forward(intersect);

  const int width = int(ext.maxx() + 0.5) - int(ext.minx() + 0.5);
  const int height = int(ext.maxy() + 0.5) - int(ext.miny() + 0.5);

  if (multi_tiles_) {
    tiled_multi_file_policy policy(datas_, tile_size_, tile_stride_, extent_,
                                   q.get_bbox(), width_, height_);
    return std::make_shared<raster_featureset<tiled_multi_file_policy>>(
        policy, extent_, q);
  } else if (width * height > static_cast<int>(tile_size_ * tile_size_ << 2)) {
    tiled_file_policy policy(data_, tile_size_, extent_, q.get_bbox(), width_,
                             height_);
    return std::make_shared<raster_featureset<tiled_file_policy>>(policy,
                                                                  extent_, q);
  } else {
    auto reader =
        std::make_shared<raster_tiled_reader>(data_, extent_, width_, height_);
    single_file_policy policy(reader);
    return std::make_shared<raster_featureset<single_file_policy>>(policy,
                                                                   extent_, q);
  }
}

featureset_ptr raster_datasource::features_at_point(coord2d const &,
                                                    double tol) const {
  return mapnik::make_invalid_featureset();
}
} // namespace nik
} // namespace flywave
