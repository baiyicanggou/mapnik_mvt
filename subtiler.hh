#pragma once

#include <chrono>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <protozero/pbf_reader.hpp>
#include <protozero/pbf_writer.hpp>

#include <mapnik/box2d.hpp>
#include <mapnik/box2d_impl.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/unicode.hpp>

#include <vector_tile_datasource_pbf.hpp>
#include <vector_tile_geometry_decoder.hpp>

#include "filter_table.hh"
#include "mvt_tile.hh"
#include "tile.hh"

namespace flywave {
namespace nik {

using tag_type = std::pair<size_t, mapnik::value>;

struct push_tag_visitor {
  const mapnik::transcoder &tr_;
  std::map<std::string, tag_type> &tags_;
  std::string const &name_;
  size_t key_index_;

  explicit push_tag_visitor(const mapnik::transcoder &tr,
                            std::map<std::string, tag_type> &tags,
                            std::string const &name, size_t key_index)
      : tr_(tr), tags_(tags), name_(name), key_index_(key_index) {}

  void operator()(std::string const &val) {
    tags_.emplace(
        name_, tag_type(key_index_, tr_.transcode(val.data(), val.length())));
  }

  void operator()(bool const &val) {
    tags_.emplace(name_,
                  tag_type(key_index_, static_cast<mapnik::value_bool>(val)));
  }

  void operator()(int64_t const &val) {
    tags_.emplace(
        name_, tag_type(key_index_, static_cast<mapnik::value_integer>(val)));
  }

  void operator()(uint64_t const &val) {
    tags_.emplace(
        name_, tag_type(key_index_, static_cast<mapnik::value_integer>(val)));
  }

  void operator()(double const &val) {
    tags_.emplace(name_,
                  tag_type(key_index_, static_cast<mapnik::value_double>(val)));
  }

  void operator()(float const &val) {
    tags_.emplace(name_,
                  tag_type(key_index_, static_cast<mapnik::value_double>(val)));
  }
};

static const mapnik::value default_feature_value{};

class feature_tags {
public:
  inline void push(const std::string &key, size_t key_index,
                   const mapnik::vector_tile_impl::pbf_attr_value_type &value,
                   const mapnik::transcoder &transcoder) {
    push_tag_visitor ptv(transcoder, tags_, key, key_index);
    mapnik::util::apply_visitor(ptv, value);
  }

  inline const mapnik::value &get(const std::string &key) const {
    auto tag_itr = tags_.find(key);
    if (tag_itr == tags_.end()) {
      return default_feature_value;
    }
    return tag_itr->second.second;
  }

  inline const mapnik::geometry::geometry<double> get_geometry() const
      noexcept {
    return mapnik::geometry::geometry_empty{};
  }

  inline const std::map<std::string, tag_type> &tags_map() const noexcept {
    return tags_;
  };

private:
  std::map<std::string, tag_type> tags_;
};

struct to_tile_value_pbf {
public:
  using Value_Encoding = mapnik::vector_tile_impl::Value_Encoding;

  explicit to_tile_value_pbf(protozero::pbf_writer &value) : value_(value) {}

  void operator()(mapnik::value_integer val) const {
    value_.add_int64(Value_Encoding::INT, val);
  }

  void operator()(mapnik::value_bool val) const {
    value_.add_bool(Value_Encoding::BOOL, val);
  }

  void operator()(mapnik::value_double val) const {
    float fval = static_cast<float>(val);
    if (val == static_cast<double>(fval)) {
      value_.add_float(Value_Encoding::FLOAT, fval);
    } else {
      value_.add_double(Value_Encoding::DOUBLE, val);
    }
  }

  void operator()(mapnik::value_unicode_string const &val) const {
    std::string str;
    mapnik::to_utf8(val, str);
    value_.add_string(Value_Encoding::STRING, str);
  }

  void operator()(mapnik::value_null const & /*val*/) const {
    // do nothing
  }

private:
  protozero::pbf_writer &value_;
};

class subtiler {
public:
  subtiler(const std::string &data, const tile_ext_id &id,
           std::shared_ptr<const filter_table> filter_table = nullptr);
  subtiler(const mvt_tile &base_tile,
           std::shared_ptr<const filter_table> filter_table = nullptr);

  std::string
  make_subtiler(const tile_id &target_tile_id, unsigned target_extent = 4096,
                int buffer_size = 16,
                std::unique_ptr<std::set<std::string>> layers = nullptr);

private:
  using packed_uint_32_t =
      protozero::iterator_range<protozero::pbf_reader::const_uint32_iterator>;
  using point_t = std::pair<int64_t, int64_t>;
  using line_t = std::vector<point_t>;

  void update_target_params(unsigned target_x, unsigned target_y,
                            unsigned source_extent, unsigned target_extent);
  void process_layer(protozero::pbf_reader *layer_pbf,
                     protozero::pbf_writer *output_pbf);
  bool
  process_feature(protozero::pbf_reader *feature_pbf,
                  std::unordered_map<mapnik::value, size_t> *layer_new_tags,
                  protozero::pbf_writer *output_layer_pbf);
  std::unique_ptr<feature_tags>
  decode_feature_tags(const packed_uint_32_t &packed_tags);

  bool process_geometry(const packed_uint_32_t &packed_geometry, int geom_type,
                        protozero::pbf_writer *output_feature_pbf);
  bool process_point(const packed_uint_32_t &packed_point,
                     protozero::packed_field_uint32 *output_geometry);
  bool process_line_string(const packed_uint_32_t &packed_linestring,
                           protozero::packed_field_uint32 *output_geometry);
  bool process_polygon(const packed_uint_32_t &packed_polygon,
                       protozero::packed_field_uint32 *output_geometry);

  inline void write_points(const std::vector<point_t> &points,
                           protozero::packed_field_uint32 *output_geometry);
  inline bool write_line_string(
      const mapnik::geometry::multi_line_string<int64_t> &multi_line,
      protozero::packed_field_uint32 *output_geometry);

  inline bool
  write_ring(const mapnik::geometry::linear_ring<std::int64_t> &linear_ring,
             int64_t &start_x, int64_t &start_y,
             protozero::packed_field_uint32 *output_geometry);

  void
  write_feature_tags(const feature_tags &feature_tags,
                     std::unordered_map<mapnik::value, size_t> *layer_new_tags,
                     protozero::pbf_writer *output_feature_pbf);

  inline void scale_and_offset(int64_t *x, int64_t *y) const {
    *x = static_cast<int64_t>(
        std::round((*x - target_offset_x_) * target_scale_));
    *y = static_cast<int64_t>(
        std::round((*y - target_offset_y_) * target_scale_));
  }

  inline unsigned encode_length(unsigned len) { return (len << 3u) | 2u; }

  inline double calculate_segment_area(int64_t const x0, int64_t const y0,
                                       int64_t const x1, int64_t const y1) {
    return (static_cast<double>(x0) * static_cast<double>(y1)) -
           (static_cast<double>(y0) * static_cast<double>(x1));
  }

  inline bool area_is_clockwise(double area) { return (area < 0.0); }

  template <typename Geometry>
  inline size_t repeated_point_count(Geometry const &geom) {
    if (geom.size() < 2) {
      return 0;
    }
    size_t count = 0;
    auto itr = geom.begin();

    for (auto prev_itr = itr++; itr != geom.end(); ++prev_itr, ++itr) {
      if (itr->x == prev_itr->x && itr->y == prev_itr->y) {
        count++;
      }
    }
    return count;
  }

  std::string tile_data_;
  tile_ext_id tile_id_;

  mapnik::box2d<int64_t> clip_box_;
  mapnik::geometry::linear_ring<std::int64_t> clip_polygon_;

  double target_scale_;
  int target_extent_;
  int target_offset_x_;
  int target_offset_y_;
  int zoom_factor_;

  std::shared_ptr<const filter_table> filter_table_;
  mapnik::expression_ptr layer_filter_;
  std::vector<std::string> layer_keys_;
  mapnik::vector_tile_impl::layer_pbf_attr_type layer_values_;
  size_t num_keys_;
  size_t num_values_;
  const mapnik::transcoder transcoder_;
  using vars_t = std::map<std::string, mapnik::value>;
  const vars_t vars_;
};
} // namespace nik
} // namespace flywave
