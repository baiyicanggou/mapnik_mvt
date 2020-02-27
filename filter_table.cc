#include "filter_table.hh"

#include <mapnik/expression_node.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/rule.hpp>

namespace flywave {
namespace nik {
namespace {
inline double zoom_to_scale_denominator(unsigned zoom) {
  return 559082264 / std::pow(2, zoom);
}

inline double scale_denominator_to_zoom(double scale_denominator) {
  return std::log2(559082264 / scale_denominator);
}
} // namespace

static inline mapnik::expression_ptr
merge_filters(const mapnik::expression_ptr &filter1,
              const mapnik::expression_ptr &filter2) noexcept {
  mapnik::binary_node<mapnik::tags::logical_or> new_filter(*filter1, *filter2);
  return std::make_shared<mapnik::expr_node>(std::move(new_filter));
}

static mapnik::expression_ptr
merge_filters(const std::vector<mapnik::expression_ptr> &filters) noexcept {
  if (filters.empty()) {
    return nullptr;
  }
  auto filter_itr = filters.begin();
  mapnik::expression_ptr result = *filter_itr;
  for (++filter_itr; filter_itr != filters.end(); ++filter_itr) {
    result = merge_filters(*filter_itr, result);
  }
  return result;
}

filter_table::filter_table(int zoom_offset, unsigned min_zoom,
                           unsigned max_zoom)
    : zoom_offset_(zoom_offset), min_zoom_(min_zoom), max_zoom_(max_zoom) {}

std::unique_ptr<filter_table> filter_table::create_filter_table(
    const std::string &map_path, const filter_table::zoom_groups_t *zoom_groups,
    int zoom_offset, uint min_zoom, uint max_zoom) {
  mapnik::Map map{};
  mapnik::load_map(map, map_path);
  return create_filter_table(map, zoom_groups, zoom_offset, min_zoom, max_zoom);
}

std::unique_ptr<filter_table> filter_table::create_filter_table(
    const mapnik::Map &map, const filter_table::zoom_groups_t *zoom_groups,
    int zoom_offset, unsigned min_zoom, unsigned max_zoom) {
  std::unique_ptr<filter_table> ftable(
      new filter_table(zoom_offset, min_zoom, max_zoom));
  ftable->parse_map(map, zoom_groups);
  return ftable;
}

void filter_table::parse_map(const mapnik::Map &map,
                             const zoom_groups_t *zoom_groups) {
  if (zoom_groups) {
    for (unsigned zoom : *zoom_groups) {
      filter_table_[zoom] = {};
    }
  } else {
    for (unsigned zoom = min_zoom_; zoom <= max_zoom_; ++zoom) {
      filter_table_[zoom] = {};
    }
  }
  if (filter_table_.empty()) {
    return;
  }

  for (auto zoom_itr = filter_table_.begin(); zoom_itr != filter_table_.end();
       ++zoom_itr) {
    unsigned zoom = zoom_itr->first;
    auto next_zoom_itr = std::next(zoom_itr);
    unsigned next_zoom =
        next_zoom_itr != filter_table_.end() ? next_zoom_itr->first : max_zoom_;

    double max_sd = zoom_to_scale_denominator(zoom + zoom_offset_) + 1e-6;
    double min_sd = zoom_to_scale_denominator(next_zoom + zoom_offset_) + 1e-6;

    struct LayerFilters {
      std::vector<mapnik::expression_ptr> filters;
      bool no_filters{false};
    };

    std::unordered_map<std::string, LayerFilters> filters;
    const auto &styles = map.styles();
    for (const mapnik::layer &layer : map.layers()) {
      const std::string &lyr_name = layer.name();
      if (lyr_name.empty()) {
        continue;
      }
      LayerFilters &layer_filters = filters[lyr_name];
      if (layer_filters.no_filters) {
        continue;
      }
      for (const auto &style_name : layer.styles()) {
        const auto style_itr = styles.find(style_name);
        if (style_itr == styles.end()) {
          continue;
        }
        for (const mapnik::rule &rule : style_itr->second.get_rules()) {
          if (max_sd < rule.get_min_scale() || min_sd >= rule.get_max_scale()) {
            continue;
          }
          mapnik::expression_ptr filter = rule.get_filter();
          if (filter == nullptr || layer_filters.filters.size() == 1000) {
            layer_filters.no_filters = true;
            layer_filters.filters.clear();
            break;
          }
          layer_filters.filters.push_back(std::move(filter));
        }
        if (layer_filters.no_filters) {
          break;
        }
      }
    }

    filter_map_t &filters_map = zoom_itr->second;
    for (auto layer_itr = filters.cbegin(); layer_itr != filters.cend();
         ++layer_itr) {
      const std::string &layer_name = layer_itr->first;
      const LayerFilters &layer_filters = layer_itr->second;
      if (layer_filters.no_filters) {
        filters_map[layer_name] = nullptr;
      } else if (!layer_filters.filters.empty()) {
        filters_map[layer_name] = merge_filters(layer_filters.filters);
      }
    }
  }
}

const filter_table::filter_map_t *
filter_table::get_filters_map(unsigned zoom) const noexcept {
  if (zoom < min_zoom_ || zoom > max_zoom_) {
    return nullptr;
  }
  auto zoom_itr = filter_table_.lower_bound(zoom);
  if (zoom_itr == filter_table_.end()) {
    return nullptr;
  }
  return &zoom_itr->second;
}
} // namespace nik
} // namespace flywave
