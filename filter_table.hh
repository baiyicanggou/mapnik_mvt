#pragma once

#include <mapnik/expression.hpp>
#include <mapnik/map.hpp>

namespace flywave {
namespace nik {

class filter_table {
public:
  using zoom_groups_t = std::set<unsigned>;
  using filter_map_t = std::unordered_map<std::string, mapnik::expression_ptr>;

  static std::unique_ptr<filter_table> create_filter_table(
      const std::string &map_path, const zoom_groups_t *zoom_groups = nullptr,
      int zoom_offset = 0, unsigned min_zoom = 0, unsigned max_zoom = 22);

  static std::unique_ptr<filter_table> create_filter_table(
      const mapnik::Map &map, const zoom_groups_t *zoom_groups = nullptr,
      int zoom_offset = 0, unsigned min_zoom = 0, unsigned max_zoom = 22);

  const filter_map_t *get_filters_map(unsigned zoom) const noexcept;

  inline zoom_groups_t *zoom_groups() const noexcept { return zoom_groups_; }

  inline unsigned max_zoom() const noexcept { return max_zoom_; }

private:
  filter_table(int zoom_offset, unsigned min_zoom = 0, unsigned max_zoom = 22);

  void parse_map(const mapnik::Map &map, const zoom_groups_t *zoom_groups);

  std::map<unsigned, filter_map_t> filter_table_;
  const int zoom_offset_;
  const unsigned min_zoom_;
  const unsigned max_zoom_;
  zoom_groups_t *zoom_groups_{nullptr};
};
} // namespace nik
} // namespace flywave
