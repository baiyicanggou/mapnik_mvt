#include "subtiler.hh"

#include <cmath>

#include <mapnik/expression_evaluator.hpp>

#include <iostream>
#include <vector_tile_geometry_clipper.hpp>

#include "bbox_clipper.hh"
#include "clipper.hh"
#include "util.hh"

namespace flywave {
namespace nik {

subtiler::subtiler(const std::string &data, const tile_ext_id &id,
                   std::shared_ptr<const filter_table> filter_table)
    : tile_data_(data), tile_id_(id), filter_table_(filter_table),
      transcoder_("utf-8") {}

subtiler::subtiler(const mvt_tile &base_tile,
                   std::shared_ptr<const filter_table> filter_table)
    : tile_data_(base_tile.get_data()), tile_id_(base_tile.id),
      filter_table_(filter_table), transcoder_("utf-8") {}

std::string
subtiler::make_subtiler(const tile_id &target_tile_id, unsigned target_extent,
                        int buffer_size,
                        std::unique_ptr<std::set<std::string>> layers) {
  std::string result;
  target_extent_ = target_extent;
  zoom_factor_ = std::pow(2, target_tile_id.z - tile_id_.id().z);
  clip_box_ = mapnik::box2d<int64_t>(-buffer_size, -buffer_size,
                                     target_extent + buffer_size,
                                     target_extent + buffer_size);

  clip_polygon_.reserve(5);
  clip_polygon_.emplace_back(clip_box_.minx(), clip_box_.miny());
  clip_polygon_.emplace_back(clip_box_.maxx(), clip_box_.miny());
  clip_polygon_.emplace_back(clip_box_.maxx(), clip_box_.maxy());
  clip_polygon_.emplace_back(clip_box_.minx(), clip_box_.maxy());
  clip_polygon_.emplace_back(clip_box_.minx(), clip_box_.miny());

  //    result.reserve(tile_data_.size() / zoom_factor);

  protozero::pbf_reader tile_message(tile_data_);
  protozero::pbf_writer result_pbf(result);

  const filter_table::filter_map_t *filter_map = nullptr;
  if (filter_table_) {
    filter_map = filter_table_->get_filters_map(target_tile_id.z);
    if (!filter_map) {
      return "";
    }
  }

  while (tile_message.next(mapnik::vector_tile_impl::Tile_Encoding::LAYERS)) {
    auto data_pair = tile_message.get_data();
    protozero::pbf_reader layer_message(data_pair);
    if (!layer_message.next(mapnik::vector_tile_impl::Layer_Encoding::NAME)) {
      continue;
    }
    std::string layer_name = layer_message.get_string();

    if (layers != nullptr && layers->find(layer_name) == layers->end()) {
      continue;
    }
    if (filter_map) {
      auto filter_itr = filter_map->find(layer_name);
      if (filter_itr == filter_map->end()) {
        continue;
      }
      layer_filter_ = filter_itr->second;
    }
    if (!layer_message.next(mapnik::vector_tile_impl::Layer_Encoding::EXTENT)) {
      continue;
    }
    unsigned layer_extent = layer_message.get_uint32();
    update_target_params(target_tile_id.x, target_tile_id.y, layer_extent,
                         target_extent);

    protozero::pbf_reader layer_pbf(data_pair);
    process_layer(&layer_pbf, &result_pbf);
  }
  return result;
}

void subtiler::update_target_params(unsigned target_x, unsigned target_y,
                                    unsigned source_extent,
                                    unsigned target_extent) {
  target_scale_ =
      target_extent * zoom_factor_ / static_cast<double>(source_extent);
  target_offset_x_ = target_x * source_extent;
  target_offset_y_ = target_y * source_extent;
}

void subtiler::process_layer(protozero::pbf_reader *layer_pbf,
                             protozero::pbf_writer *output_pbf) {
  using Layer_Encoding = mapnik::vector_tile_impl::Layer_Encoding;
  using Value_Encoding = mapnik::vector_tile_impl::Value_Encoding;
  using pbf_pair_t = std::pair<const char *, protozero::pbf_length_type>;
  std::string name;
  std::vector<pbf_pair_t> keys, values;
  unsigned version = 0;

  std::vector<protozero::pbf_reader> features;
  protozero::pbf_writer output_layer_pbf(
      *output_pbf, mapnik::vector_tile_impl::Tile_Encoding::LAYERS);

  layer_keys_.clear();
  layer_values_.clear();

  while (layer_pbf->next()) {
    switch (layer_pbf->tag()) {
    case Layer_Encoding::NAME:
      name = layer_pbf->get_string();
      break;
    case Layer_Encoding::FEATURES:
      features.push_back(layer_pbf->get_message());
      break;
    case Layer_Encoding::KEYS:
      if (layer_filter_ == nullptr) {
        keys.push_back(layer_pbf->get_data());
      } else {
        layer_keys_.push_back(layer_pbf->get_string());
      }
      break;
    case Layer_Encoding::VALUES:
      if (layer_filter_ == nullptr) {
        values.push_back(layer_pbf->get_data());
      } else {
        protozero::pbf_reader val_msg = layer_pbf->get_message();
        while (val_msg.next()) {
          switch (val_msg.tag()) {
          case Value_Encoding::STRING:
            layer_values_.push_back(val_msg.get_string());
            break;
          case Value_Encoding::FLOAT:
            layer_values_.push_back(val_msg.get_float());
            break;
          case Value_Encoding::DOUBLE:
            layer_values_.push_back(val_msg.get_double());
            break;
          case Value_Encoding::INT:
            layer_values_.push_back(val_msg.get_int64());
            break;
          case Value_Encoding::UINT:
            layer_values_.push_back(val_msg.get_uint64());
            break;
          case Value_Encoding::SINT:
            layer_values_.push_back(val_msg.get_sint64());
            break;
          case Value_Encoding::BOOL:
            layer_values_.push_back(val_msg.get_bool());
            break;
          }
        }
      }
      break;
    case Layer_Encoding::VERSION:
      version = layer_pbf->get_uint32();
      break;
    case Layer_Encoding::EXTENT:
      layer_pbf->get_uint32();
      break;
    }
  }

  num_keys_ = layer_keys_.size();
  num_values_ = layer_values_.size();
  std::unordered_map<mapnik::value, size_t> layer_new_tags;
  bool features_written = false;
  for (auto feature_pbf : features) {
    if (process_feature(&feature_pbf, &layer_new_tags, &output_layer_pbf)) {
      features_written = true;
    }
  }

  if (!features_written) {
    output_layer_pbf.rollback();
    return;
  }

  output_layer_pbf.add_message(Layer_Encoding::NAME, name);

  if (layer_filter_ == nullptr) {
    for (const auto &key : keys) {
      output_layer_pbf.add_message(Layer_Encoding::KEYS, key.first, key.second);
    }
    for (const auto &value : values) {
      output_layer_pbf.add_message(Layer_Encoding::VALUES, value.first,
                                   value.second);
    }
  } else {
    for (const auto &key : layer_keys_) {
      output_layer_pbf.add_message(Layer_Encoding::KEYS, key);
    }
    std::vector<mapnik::value> tags_vector;
    size_t num_tags = layer_new_tags.size();
    tags_vector.resize(num_tags);
    for (auto &tag_itr : layer_new_tags) {
      if (tag_itr.second < num_tags) {
        tags_vector[tag_itr.second] = std::move(tag_itr.first);
      }
    }
    for (const auto &tag_itr : tags_vector) {
      protozero::pbf_writer value_writer(output_layer_pbf,
                                         Layer_Encoding::VALUES);
      to_tile_value_pbf visitor(value_writer);
      mapnik::util::apply_visitor(visitor, tag_itr);
    }
  }
  output_layer_pbf.add_uint32(Layer_Encoding::EXTENT,
                              static_cast<uint>(target_extent_));
  output_layer_pbf.add_uint32(Layer_Encoding::VERSION, version);
}

bool subtiler::process_feature(
    protozero::pbf_reader *feature_pbf,
    std::unordered_map<mapnik::value, size_t> *layer_new_tags,
    protozero::pbf_writer *output_layer_pbf) {
  using Feature_Encoding = mapnik::vector_tile_impl::Feature_Encoding;
  uint64_t id = 0;
  int geom_type = 0;
  std::vector<packed_uint_32_t> tags, geometrys;
  std::unique_ptr<feature_tags> decoded_tags;
  protozero::pbf_writer output_feature_pbf(
      *output_layer_pbf, mapnik::vector_tile_impl::Layer_Encoding::FEATURES);
  while (feature_pbf->next()) {
    switch (feature_pbf->tag()) {
    case Feature_Encoding::ID:
      id = feature_pbf->get_uint64();
      break;
    case Feature_Encoding::GEOMETRY:
      geometrys.push_back(std::move(feature_pbf->get_packed_uint32()));
      break;
    case Feature_Encoding::RASTER:
      output_feature_pbf.rollback();
      return false;
    case Feature_Encoding::TAGS:
      if (layer_filter_ == nullptr) {
        tags.push_back(std::move(feature_pbf->get_packed_uint32()));
      } else {
        decoded_tags = decode_feature_tags(feature_pbf->get_packed_uint32());
        mapnik::value_type result = mapnik::util::apply_visitor(
            mapnik::evaluate<feature_tags, mapnik::value, vars_t>(*decoded_tags,
                                                                  vars_),
            *layer_filter_);
        if (!result.to_bool()) {
          output_feature_pbf.rollback();
          return false;
        }
      }
      break;
    case Feature_Encoding::TYPE:
      geom_type = feature_pbf->get_enum();
      break;
    default:
      output_feature_pbf.rollback();
      return false;
    }
  }

  bool geometries_written = false;
  for (auto &geometry : geometrys) {
    if (process_geometry(geometry, geom_type, &output_feature_pbf)) {
      geometries_written = true;
    }
  }
  if (!geometries_written) {
    output_feature_pbf.rollback();
    return false;
  }

  output_feature_pbf.add_uint64(Feature_Encoding::ID, id);
  output_feature_pbf.add_enum(Feature_Encoding::TYPE, geom_type);
  if (layer_filter_ == nullptr) {
    for (auto &tag : tags) {
      output_feature_pbf.add_packed_uint32(Feature_Encoding::TAGS, tag.first,
                                           tag.second);
    }
  } else if (decoded_tags != nullptr) {
    write_feature_tags(*decoded_tags, layer_new_tags, &output_feature_pbf);
  }
  return true;
}

std::unique_ptr<feature_tags>
subtiler::decode_feature_tags(const subtiler::packed_uint_32_t &packed_tags) {
  auto ftags = std::make_unique<feature_tags>();
  for (auto _i = packed_tags.begin(); _i != packed_tags.end();) {
    size_t key_index = *(_i++);
    if (_i == packed_tags.end()) {
      return nullptr;
    }
    size_t key_value = *(_i++);
    if (key_index < num_keys_ && key_value < num_values_) {
      std::string const &key_name = layer_keys_.at(key_index);
      const mapnik::vector_tile_impl::pbf_attr_value_type &val =
          layer_values_.at(key_value);
      ftags->push(key_name, key_index, val, transcoder_);
    }
  }
  return ftags;
}

void subtiler::write_feature_tags(
    const feature_tags &feature_tags,
    std::unordered_map<mapnik::value, size_t> *layer_new_tags,
    protozero::pbf_writer *output_feature_pbf) {
  std::vector<std::uint32_t> encoded_feature_tags;
  encoded_feature_tags.reserve(feature_tags.tags_map().size());
  for (const auto tag_itr : feature_tags.tags_map()) {
    const tag_type &tag = tag_itr.second;
    if (tag.second.is_null()) {
      continue;
    }
    encoded_feature_tags.push_back(static_cast<uint32_t>(tag.first));
    const auto val_itr = layer_new_tags->find(tag.second);
    if (val_itr == layer_new_tags->end()) {
      size_t index = layer_new_tags->size();
      layer_new_tags->emplace(tag.second, index);
      encoded_feature_tags.push_back(static_cast<uint32_t>(index));
    } else {
      encoded_feature_tags.push_back(static_cast<uint32_t>(val_itr->second));
    }
  }
  output_feature_pbf->add_packed_uint32(
      mapnik::vector_tile_impl::Feature_Encoding::TAGS,
      encoded_feature_tags.begin(), encoded_feature_tags.end());
}

bool subtiler::process_geometry(
    const subtiler::packed_uint_32_t &packed_geometry, int geom_type,
    protozero::pbf_writer *output_feature_pbf) {
  protozero::packed_field_uint32 output_packed_geometry(
      *output_feature_pbf,
      mapnik::vector_tile_impl::Feature_Encoding::GEOMETRY);
  using Geometry_Type = mapnik::vector_tile_impl::Geometry_Type;
  bool geom_written = false;
  switch (geom_type) {
  case Geometry_Type::UNKNOWN:
    break;
  case Geometry_Type::POINT:
    if (process_point(packed_geometry, &output_packed_geometry)) {
      geom_written = true;
    }
    break;
  case Geometry_Type::LINESTRING:
    if (process_line_string(packed_geometry, &output_packed_geometry)) {
      geom_written = true;
    }
    break;
  case Geometry_Type::POLYGON:
    if (process_polygon(packed_geometry, &output_packed_geometry)) {
      geom_written = true;
    }
    break;
  default:
    break;
  }
  if (!geom_written) {
    output_packed_geometry.rollback();
    return false;
  }
  return true;
}

bool subtiler::process_point(const subtiler::packed_uint_32_t &packed_points,
                             protozero::packed_field_uint32 *output_geometry) {
  mapnik::vector_tile_impl::GeometryPBF point(packed_points);
  int64_t x, y;
  std::vector<point_t> points;
  while (point.point_next(x, y)) {
    scale_and_offset(&x, &y);
    if (clip_box_.contains(x, y)) {
      points.emplace_back(x, y);
    }
  }
  if (points.empty()) {
    return false;
  }
  write_points(points, output_geometry);
  return true;
}

bool subtiler::process_line_string(
    const subtiler::packed_uint_32_t &packed_linestring,
    protozero::packed_field_uint32 *output_geometry) {
  using GeometryPBF = mapnik::vector_tile_impl::GeometryPBF;
  GeometryPBF linestring(packed_linestring);
  int64_t x0, y0, x1, y1;
  GeometryPBF::command cmd;
  cmd = linestring.line_next(x0, y0, false);
  if (cmd == GeometryPBF::end) {
    return false;
  } else if (cmd != GeometryPBF::move_to) {
    return false;
  }
  mapnik::geometry::multi_line_string<int64_t> results;

  while (true) {
    cmd = linestring.line_next(x1, y1, true);
    if (cmd != GeometryPBF::line_to) {
      return false;
    }
    mapnik::geometry::line_string<int64_t> line;

    line.reserve(linestring.get_length() + 2);
    scale_and_offset(&x0, &y0);
    line.add_coord(x0, y0);
    scale_and_offset(&x1, &y1);
    line.add_coord(x1, y1);
    while ((cmd = linestring.line_next(x1, y1, true)) == GeometryPBF::line_to) {
      scale_and_offset(&x1, &y1);
      line.add_coord(x1, y1);
    }

    bbox_clipper::clip_line_string(line, clip_box_, &results);

    if (cmd == GeometryPBF::end) {
      break;
    }
    x0 = x1;
    y0 = y1;
  }

  return write_line_string(results, output_geometry);
}

namespace detail {

inline bool clip_multi_polygon(
    mapnik::geometry::multi_polygon<std::int64_t> &mp,
    std::vector<std::unique_ptr<ClipperLib::PolyTree>> &output_polygons,
    const mapnik::geometry::linear_ring<std::int64_t> &clip_polygon) {
  ClipperLib::Clipper clipper;
  clipper.StrictlySimple(true);

  for (auto &poly : mp) {
    ClipperLib::CleanPolygon(poly.exterior_ring, 1.415);
    double outer_area = ClipperLib::Area(poly.exterior_ring);
    if (std::abs(outer_area) < 0.1) {
      continue;
    }

    if (outer_area < 0) {
      std::reverse(poly.exterior_ring.begin(), poly.exterior_ring.end());
    }
    if (!clipper.AddPath(poly.exterior_ring, ClipperLib::ptSubject, true)) {
      continue;
    }
    for (auto &interior_ring : poly.interior_rings) {
      if (interior_ring.size() < 3) {
        continue;
      }
      ClipperLib::CleanPolygon(interior_ring, 1.415);
      double inner_area = ClipperLib::Area(interior_ring);
      if (std::abs(inner_area) < 0.1) {
        continue;
      }
      if (inner_area > 0) {
        std::reverse(interior_ring.begin(), interior_ring.end());
      }
      clipper.AddPath(interior_ring, ClipperLib::ptSubject, true);
    }
    if (!clipper.AddPath(clip_polygon, ClipperLib::ptClip, true)) {
      continue;
    }
    output_polygons.emplace_back(new ClipperLib::PolyTree());
    clipper.Execute(ClipperLib::ctIntersection, *output_polygons.back().get(),
                    ClipperLib::pftPositive, ClipperLib::pftEvenOdd);
    clipper.Clear();
  }
  return true;
}

inline void
process_polynode_branch(ClipperLib::PolyNode *polynode,
                        mapnik::geometry::multi_polygon<std::int64_t> &mp,
                        double area_threshold) {
  mapnik::geometry::polygon<std::int64_t> polygon;
  polygon.set_exterior_ring(std::move(polynode->Contour));
  if (polygon.exterior_ring.size() > 2) {
    double outer_area = ClipperLib::Area(polygon.exterior_ring);
    if (std::abs(outer_area) >= area_threshold) {
      if (outer_area < 0) {
        std::reverse(polygon.exterior_ring.begin(),
                     polygon.exterior_ring.end());
      }

      for (auto *ring : polynode->Childs) {
        if (ring->Contour.size() < 3) {
          continue;
        }
        double inner_area = ClipperLib::Area(ring->Contour);
        if (std::abs(inner_area) < area_threshold) {
          continue;
        }

        if (inner_area > 0) {
          std::reverse(ring->Contour.begin(), ring->Contour.end());
        }
        polygon.add_hole(std::move(ring->Contour));
      }
      mp.push_back(std::move(polygon));
    }
  }
  for (auto *ring : polynode->Childs) {
    for (auto *sub_ring : ring->Childs) {
      process_polynode_branch(sub_ring, mp, area_threshold);
    }
  }
}

} // namespace detail

bool subtiler::process_polygon(
    const packed_uint_32_t &packed_polygon,
    protozero::packed_field_uint32 *output_geometry) {
  using GeometryPBF = mapnik::vector_tile_impl::GeometryPBF;
  GeometryPBF::command cmd;
  int64_t x0, y0;
  int64_t x1, y1;
  int64_t x2, y2;

  int64_t x0_, y0_;
  int64_t x1_, y1_;
  int64_t x2_, y2_;

  GeometryPBF polygon(packed_polygon);

  bool first_ring = true;
  bool looking_for_exterior = true;
  bool current_is_exterior;
  bool has_next_geometry = true;

  cmd = polygon.ring_next(x0, y0, false);
  if (cmd == GeometryPBF::end) {
    return false;
  } else if (cmd != GeometryPBF::move_to) {
    return false;
  }

  bool geometry_written = false;

  mapnik::geometry::multi_polygon<std::int64_t> decoded_mp;
  mapnik::geometry::polygon<std::int64_t> *decoded_polygon;

  while (has_next_geometry) {
    double ring_area = 0.0;
    mapnik::box2d<int64_t> part_env;

    mapnik::geometry::linear_ring<std::int64_t> decoded_ring;

    x0_ = x0;
    y0_ = y0;
    scale_and_offset(&x0, &y0);

    cmd = polygon.ring_next(x1, y1, true);
    if (cmd != GeometryPBF::line_to) {
      return false;
    }
    x1_ = x1;
    y1_ = y1;
    scale_and_offset(&x1, &y1);

    cmd = polygon.ring_next(x2, y2, true);
    if (cmd != GeometryPBF::line_to) {
      return false;
    }
    x2_ = x2;
    y2_ = y2;
    scale_and_offset(&x2, &y2);

    decoded_ring.reserve(polygon.get_length() + 4);

    decoded_ring.add_coord(x0, y0);
    part_env.init(x0, y0, x0, y0);

    decoded_ring.add_coord(x1, y1);
    part_env.expand_to_include(x1, y1);
    ring_area += calculate_segment_area(x0_, y0_, x1_, y1_);

    decoded_ring.add_coord(x2, y2);
    part_env.expand_to_include(x2, y2);
    ring_area += calculate_segment_area(x1_, y1_, x2_, y2_);
    x1_ = x2_;
    y1_ = y2_;

    while ((cmd = polygon.ring_next(x2, y2, true)) == GeometryPBF::line_to) {
      x2_ = x2;
      y2_ = y2;
      scale_and_offset(&x2, &y2);
      decoded_ring.add_coord(x2, y2);
      part_env.expand_to_include(x2, y2);
      ring_area += calculate_segment_area(x1_, y1_, x2_, y2_);
      x1_ = x2_;
      y1_ = y2_;
    }
    if (cmd != GeometryPBF::close) {
      return false;
    }
    if (decoded_ring.back().x != x0 || decoded_ring.back().y != y0) {
      decoded_ring.add_coord(x0, y0);
      ring_area += calculate_segment_area(x1_, y1_, x0_, y0_);
    }

    cmd = polygon.ring_next(x0, y0, false);
    if (cmd == GeometryPBF::end) {
      has_next_geometry = false;
    } else if (cmd != GeometryPBF::move_to) {
      return false;
    }

    current_is_exterior = ring_area >= 0;

    if (first_ring) {
      first_ring = false;
      if (!current_is_exterior) {
        continue;
      }
    }

    if (!current_is_exterior && looking_for_exterior) {
      continue;
    }

    if (decoded_ring.size() > 2 && part_env.intersects(clip_box_)) {
      if (current_is_exterior) {
        decoded_mp.emplace_back();
        decoded_polygon = &decoded_mp.back();
        decoded_polygon->set_exterior_ring(std::move(decoded_ring));
        looking_for_exterior = false;
      } else {
        decoded_polygon->add_hole(std::move(decoded_ring));
      }
    } else if (current_is_exterior) {
      looking_for_exterior = true;
    }
  }

  std::vector<std::unique_ptr<ClipperLib::PolyTree>> output_polygons;
  if (!nik::detail::clip_multi_polygon(decoded_mp, output_polygons,
                                       clip_polygon_)) {
    return false;
  }

  int64_t start_x = 0, start_y = 0;

  for (auto &polygons : output_polygons) {

    for (auto *polynode : polygons->Childs) {
      mapnik::geometry::multi_polygon<std::int64_t> new_mp;
      nik::detail::process_polynode_branch(polynode, new_mp, 0.1);
      for (auto &new_polygon : new_mp) {
        if (!new_polygon.exterior_ring.empty() &&
            write_ring(new_polygon.exterior_ring, start_x, start_y,
                       output_geometry)) {
          geometry_written = true;
          for (auto &interior_ring : new_polygon.interior_rings) {
            write_ring(interior_ring, start_x, start_y, output_geometry);
          }
        }
      }
    }
  }
  return geometry_written;
}

void subtiler::write_points(const std::vector<subtiler::point_t> &points,
                            protozero::packed_field_uint32 *output_geometry) {
  int64_t start_x = 0, start_y = 0;
  uint32_t num_points = static_cast<uint32_t>(points.size());
  output_geometry->add_element(1u | (num_points << 3));
  for (auto &p : points) {
    int32_t dx = static_cast<uint32_t>(p.first - start_x);
    int32_t dy = static_cast<uint32_t>(p.second - start_y);
    output_geometry->add_element(protozero::encode_zigzag32(dx));
    output_geometry->add_element(protozero::encode_zigzag32(dy));
    start_x = p.first;
    start_y = p.second;
  }
}

bool subtiler::write_line_string(
    const mapnik::geometry::multi_line_string<int64_t> &multi_line,
    protozero::packed_field_uint32 *output_geometry) {
  bool success = false;
  int64_t start_x = 0, start_y = 0;
  for (auto const &line : multi_line) {
    size_t line_size = line.size();
    line_size -= repeated_point_count(line);
    if (line_size < 2) {
      continue;
    }

    success = true;

    unsigned line_to_length = static_cast<unsigned>(line_size) - 1;

    auto pt = line.begin();

    int64_t x = pt->x;
    int64_t y = pt->y;

    output_geometry->add_element(9); // move_to | (1 << 3)
    output_geometry->add_element(
        protozero::encode_zigzag32(static_cast<int32_t>(x - start_x)));
    output_geometry->add_element(
        protozero::encode_zigzag32(static_cast<int32_t>(y - start_y)));
    start_x = x;
    start_y = y;
    output_geometry->add_element(encode_length(line_to_length));
    for (++pt; pt != line.end(); ++pt) {
      x = pt->x;
      y = pt->y;
      int32_t dx = static_cast<int32_t>(x - start_x);
      int32_t dy = static_cast<int32_t>(y - start_y);
      if (dx == 0 && dy == 0) {
        continue;
      }
      output_geometry->add_element(protozero::encode_zigzag32(dx));
      output_geometry->add_element(protozero::encode_zigzag32(dy));
      start_x = x;
      start_y = y;
    }
  }
  return success;
}

bool subtiler::write_ring(
    const mapnik::geometry::linear_ring<std::int64_t> &linear_ring,
    int64_t &start_x, int64_t &start_y,
    protozero::packed_field_uint32 *output_geometry) {
  size_t ring_size = linear_ring.size();
  ring_size -= repeated_point_count(linear_ring);
  if (ring_size < 3) {
    return false;
  }
  auto last_itr = linear_ring.end();
  if (linear_ring.front() == linear_ring.back()) {
    --last_itr;
    --ring_size;
    if (ring_size < 3) {
      return false;
    }
  }
  unsigned line_to_length = static_cast<unsigned>(ring_size) - 1;
  auto pt = linear_ring.begin();
  int64_t x = pt->x;
  int64_t y = pt->y;
  output_geometry->add_element(9); // move_to | (1 << 3)
  output_geometry->add_element(
      protozero::encode_zigzag32(static_cast<int32_t>(x - start_x)));
  output_geometry->add_element(
      protozero::encode_zigzag32(static_cast<int32_t>(y - start_y)));
  start_x = x;
  start_y = y;
  output_geometry->add_element(encode_length(line_to_length));
  for (++pt; pt != last_itr; ++pt) {
    x = pt->x;
    y = pt->y;
    int32_t dx = static_cast<int32_t>(x - start_x);
    int32_t dy = static_cast<int32_t>(y - start_y);
    if (dx == 0 && dy == 0) {
      continue;
    }
    output_geometry->add_element(protozero::encode_zigzag32(dx));
    output_geometry->add_element(protozero::encode_zigzag32(dy));
    start_x = x;
    start_y = y;
  }
  output_geometry->add_element(15); // close_path
  return true;
}
} // namespace nik
} // namespace flywave
