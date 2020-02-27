#pragma once

#include <mapnik/box2d.hpp>
#include <mapnik/coord.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/image_scaling.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>
#include <mapnik/rule.hpp>

#include "tile.hh"
#include "utfgrid_encode.hh"

namespace flywave {
namespace nik {

using tile_coord = mapnik::coord<unsigned int, 2>;
using pixel_coord = mapnik::coord<unsigned int, 2>;

struct tile_bounds {
  tile_coord min;
  tile_coord max;

  unsigned int width() const { return max.x - min.x; }

  unsigned int height() const { return max.y - min.y; }
};

inline bool operator==(tile_bounds x, tile_bounds y) {
  return x.min == y.min && x.max == y.max;
}

inline bool operator!=(tile_bounds x, tile_bounds y) { return !(x == y); }

static const double MAX_ZOOM = 20.0;
static const double MIN_ZOOM = 1.0;

static const std::string default_map_proj =
    "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0.0 "
    "+k=1.0 "
    "+units=m +nadgrids=@null +wktext +no_defs +over";

static inline std::string get_tile_data(size_t x, size_t y, size_t width,
                                        size_t height,
                                        const mapnik::image_rgba8 &img) {
  mapnik::image_view<mapnik::image_rgba8> view(x, y, width, height, img);
  return mapnik::save_to_string(view, "png8:z=1");
}

static inline std::string get_tile_data(size_t x, size_t y, size_t width,
                                        size_t height,
                                        const mapnik::grid &grid) {
  mapnik::grid_view view =
      const_cast<mapnik::grid &>(grid).get_view(x, y, width, height);
  return encode_utfgrid(view);
}

template <typename T>
static void split_to_tiles(const T &image, mapnik_tile &metatile) {
  const tile_ext_id &metatile_id = metatile.id;
  assert(image.width() % metatile_id.width() == 0);
  assert(image.height() % metatile_id.height() == 0);
  size_t tile_image_width = image.width() / metatile_id.width();
  size_t tile_image_height = image.height() / metatile_id.height();
  size_t tile_i = 0;
  for (size_t y = 0; y < image.height(); y += tile_image_height) {
    for (size_t x = 0; x < image.width(); x += tile_image_width) {
      assert(tile_i < metatile.tiles.size());
      std::string &tile_data = metatile.tiles[tile_i++].data;
      tile_data =
          get_tile_data(x, y, tile_image_width, tile_image_height, image);
    }
  }
}

static inline void calculate_layers_sd(mapnik::Map &map) {
  const auto &styles = map.styles();
  for (auto &layer : map.layers()) {
    double min_sd = 1000000000;
    double max_sd = 0;
    for (const auto &style_name : layer.styles()) {
      const auto style_itr = styles.find(style_name);
      if (style_itr == styles.end()) {
        continue;
      }
      const auto &style = style_itr->second;
      for (const auto &rule : style.get_rules()) {
        min_sd = std::min(min_sd, rule.get_min_scale());
        max_sd = std::max(max_sd, rule.get_max_scale());
      }
    }
    if (min_sd != 1000000000) {
      layer.set_minimum_scale_denominator(min_sd);
    }
    if (max_sd != 0) {
      layer.set_maximum_scale_denominator(max_sd);
    }
  }
}

} // namespace nik
} // namespace flywave
