#ifndef __MAPNIK_VECTOR_TILE_GEOMETRY_ENCODER_PBF_H__
#define __MAPNIK_VECTOR_TILE_GEOMETRY_ENCODER_PBF_H__

// mapnik-vector-tile
#include "vector_tile_config.hpp"

// mapbox
#include <mapbox/geometry/geometry.hpp>

// protozero
#include <protozero/pbf_writer.hpp>
#include <protozero/varint.hpp>

// std
#include <cmath>
#include <cstdlib>

namespace mapnik {

namespace vector_tile_impl {

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::point<std::int64_t> const &pt,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::multi_point<std::int64_t> const &geom,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::line_string<std::int64_t> const &line,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

MAPNIK_VECTOR_INLINE bool encode_geometry_pbf(
    mapbox::geometry::multi_line_string<std::int64_t> const &geom,
    protozero::pbf_writer &current_feature, int32_t &start_x, int32_t &start_y);

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::polygon<std::int64_t> const &poly,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::multi_polygon<std::int64_t> const &poly,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

MAPNIK_VECTOR_INLINE bool
encode_geometry_pbf(mapbox::geometry::geometry<std::int64_t> const &geom,
                    protozero::pbf_writer &current_feature, int32_t &start_x,
                    int32_t &start_y);

} // namespace vector_tile_impl

} // namespace mapnik

#endif // __MAPNIK_VECTOR_TILE_GEOMETRY_ENCODER_PBF_H__
