#pragma once

#include "raster_data.hh"
#include "raster_datasource.hh"
#include "raster_tiled_reader.hh"

#include <mapnik/debug.hpp>
#include <mapnik/feature.hpp>

#include <vector>

#include <boost/utility.hpp>

namespace flywave {
namespace nik {

class single_file_policy {
  raster_tiled_reader_ptr info_;

public:
  class const_iterator {
    enum iterator_e { start, end };
    bool status_;
    const single_file_policy *p_;

  public:
    explicit const_iterator(const single_file_policy *p)
        : status_(start), p_(p) {}

    const_iterator() : status_(end) {}

    const_iterator(const const_iterator &other)
        : status_(other.status_), p_(other.p_) {}

    const_iterator &operator++() {
      status_ = end;
      return *this;
    }

    const raster_tiled_reader &operator*() const { return *p_->info_; }

    const raster_tiled_reader *operator->() const { return p_->info_.get(); }

    bool operator!=(const const_iterator &itr) {
      return status_ != itr.status_;
    }
  };

  explicit single_file_policy(raster_tiled_reader_ptr info) : info_(info) {}

  const_iterator begin() { return const_iterator(this); }

  const_iterator query(const mapnik::box2d<double> &box) {
    if (box.intersects(info_->envelope())) {
      return begin();
    }
    return end();
  }

  const_iterator end() { return const_iterator(); }

  inline int img_width(int reader_width) const { return reader_width; }

  inline int img_height(int reader_height) const { return reader_height; }

  inline mapnik::box2d<double> transform(mapnik::box2d<double> &) const {
    return mapnik::box2d<double>(0, 0, 0, 0);
  }
};

class tiled_file_policy {
public:
  using const_iterator = std::vector<raster_tiled_reader>::const_iterator;

  tiled_file_policy(raster_data_ptr data, unsigned tile_size,
                    mapnik::box2d<double> const &extent,
                    mapnik::box2d<double> const &bbox, unsigned width,
                    unsigned height) {
    double lox = extent.minx();
    double loy = extent.miny();

    int max_x = int(std::ceil(double(width) / double(tile_size)));
    int max_y = int(std::ceil(double(height) / double(tile_size)));

    double pixel_x = extent.width() / double(width);
    double pixel_y = extent.height() / double(height);

    mapnik::box2d<double> e = bbox.intersect(extent);

    for (int x = 0; x < max_x; ++x) {
      for (int y = 0; y < max_y; ++y) {
        double x0 = lox + x * tile_size * pixel_x;
        double y0 = loy + y * tile_size * pixel_y;
        double x1 = x0 + tile_size * pixel_x;
        double y1 = y0 + tile_size * pixel_y;

        if (e.intersects(mapnik::box2d<double>(x0, y0, x1, y1))) {
          mapnik::box2d<double> tile_box =
              e.intersect(mapnik::box2d<double>(x0, y0, x1, y1));
          raster_tiled_reader info(data, tile_box, tile_size, tile_size);
          datas_.push_back(info);
        }
      }
    }
  }

  const_iterator begin() { return datas_.begin(); }

  const_iterator end() { return datas_.end(); }

  inline int img_width(int reader_width) const { return reader_width; }

  inline int img_height(int reader_height) const { return reader_height; }

  inline mapnik::box2d<double> transform(mapnik::box2d<double> &) const {
    return mapnik::box2d<double>(0, 0, 0, 0);
  }

private:
  std::vector<raster_tiled_reader> datas_;
};

class tiled_multi_file_policy {
public:
  using const_iterator = std::vector<raster_tiled_reader>::const_iterator;

  tiled_multi_file_policy(raster_tiled_data files, unsigned tile_size,
                          unsigned tile_stride, mapnik::box2d<double> extent,
                          mapnik::box2d<double> bbox, unsigned width,
                          unsigned height)
      : image_width_(width), image_height_(height), tile_size_(tile_size),
        tile_stride_(tile_stride) {
    double lox = extent.minx();
    double loy = extent.miny();

    double pixel_x = extent.width() / double(width);
    double pixel_y = extent.height() / double(height);

    mapnik::box2d<double> e = bbox.intersect(extent);

    const int x_min = int(std::floor((e.minx() - lox) / (tile_size * pixel_x)));
    const int y_min = int(std::floor((e.miny() - loy) / (tile_size * pixel_y)));
    const int x_max = int(std::ceil((e.maxx() - lox) / (tile_size * pixel_x)));
    const int y_max = int(std::ceil((e.maxy() - loy) / (tile_size * pixel_y)));

    for (int x = x_min; x < x_max; ++x) {
      for (int y = y_min; y < y_max; ++y) {
        double x0 = lox + x * tile_size * pixel_x;
        double y0 = loy + y * tile_size * pixel_y;
        double x1 = x0 + tile_size * pixel_x;
        double y1 = y0 + tile_size * pixel_y;

        if (e.intersects(mapnik::box2d<double>(x0, y0, x1, y1))) {
          mapnik::box2d<double> tile_box =
              e.intersect(mapnik::box2d<double>(x0, y0, x1, y1));
          raster_tiled_reader info(files[y * tile_stride_ + x], tile_box,
                                   tile_size, tile_size);
          datas_.push_back(info);
        }
      }
    }
  }

  const_iterator begin() { return datas_.begin(); }

  const_iterator end() { return datas_.end(); }

  inline int img_width(int) const { return image_width_; }

  inline int img_height(int) const { return image_height_; }

  inline mapnik::box2d<double> transform(mapnik::box2d<double> &box) const {
    int x_offset = int(std::floor(box.minx() / tile_size_));
    int y_offset = int(std::floor(box.miny() / tile_size_));
    mapnik::box2d<double> rem(x_offset * tile_size_, y_offset * tile_size_,
                              x_offset * tile_size_, y_offset * tile_size_);
    box.init(box.minx() - rem.minx(), box.miny() - rem.miny(),
             box.maxx() - rem.maxx(), box.maxy() - rem.maxy());
    return rem;
  }

private:
  unsigned int image_width_, image_height_, tile_size_, tile_stride_;
  std::vector<raster_tiled_reader> datas_;
};

template <typename LookupPolicy>
class raster_featureset : public mapnik::Featureset {
  using iterator_type = typename LookupPolicy::const_iterator;

public:
  raster_featureset(LookupPolicy const &policy,
                    mapnik::box2d<double> const &exttent,
                    mapnik::query const &q);
  virtual ~raster_featureset();
  mapnik::feature_ptr next();

private:
  LookupPolicy policy_;
  mapnik::value_integer feature_id_;
  mapnik::context_ptr ctx_;
  mapnik::box2d<double> extent_;
  mapnik::box2d<double> bbox_;
  iterator_type curIter_;
  iterator_type endIter_;
  double filter_factor_;
};
} // namespace nik
} // namespace flywave
