
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")
IF (WIN32)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32/include"
                      "${CMAKE_CURRENT_SOURCE_DIR}/../libproj/arch/win/src")
ENDIF()

IF(APPLE)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac/include"
                      "${CMAKE_CURRENT_SOURCE_DIR}/../libproj/arch/unix/src")
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux/include"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../libproj/arch/unix/src")
ENDIF()

INCLUDE_DIRECTORIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/src/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libjpeg"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libpng"
    "${CMAKE_CURRENT_SOURCE_DIR}/../zlib"
    "${CMAKE_CURRENT_BINARY_DIR}/../zlib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/src/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/common/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/i18n/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../harfbuzz/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libboost/boost_1_67_0"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libproj/proj/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../webp/include"
)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/plugins")
# INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/gdal")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/json")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/deps")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/deps/mapbox/variant/include")
 
 if(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
ENDIF()
 
if (UNIX)
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals ")
ENDIF()
endif()
 
set(mapnik_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/expression_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fs.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/well_known_srs.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/params.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_filter_types.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_filter_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/conversions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_copy.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_compositing.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_scaling.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/box2d.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/datasource_cache.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/datasource_cache_static.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/debug.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry_reprojection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/expression_node.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/expression_string.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/expression.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/transform_expression.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature_kv_iterator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature_style_processor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature_type_style.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dasharray_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/font_engine_freetype.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/font_set.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/function_call.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gradient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/parse_path.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_reader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cairo_io.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_view.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_view_any.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_any.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_options.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_util_jpeg.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_util_png.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_util_tiff.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_util_webp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/layer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/load_map.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/palette.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/marker_helpers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/transform_expression_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry_envelope.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rule.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/save_map.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/wkb.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/twkb.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/projection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/proj_transform.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/scale_denominator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/simplify.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/parse_transform.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_datasource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/symbolizer_keys.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/symbolizer_enumerations.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/unicode.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raster_colorizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rapidxml_loader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mapped_memory_cache.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/marker_cache.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/svg_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/svg_path_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/svg_points_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/svg_transform_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/warp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/webp_reader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/glibc_workaround.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/css_color_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vertex_cache.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vertex_adapters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/font_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/text_layout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/text_line.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/itemizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/scrptrun.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/face.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/glyph_positions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placement_finder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/properties_util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/symbolizer_helpers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/text_properties.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/font_feature_settings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/text.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/format.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/layout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/formatting/registry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placements/registry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placements/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placements/dummy.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placements/list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/text/placements/simple.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/group/group_layout_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/group/group_rule.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/group/group_symbolizer_helper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/xml_tree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config_error.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/color_factory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer_common.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer_common/render_group_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer_common/render_markers_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer_common/render_pattern.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer_common/render_thunk_extractor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/math.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/value.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/agg_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_dot_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_building_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_line_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_line_pattern_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_text_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_point_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_polygon_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_polygon_pattern_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_raster_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_shield_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_markers_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_group_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/process_debug_symbolizer.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_markers_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_group_symbolizer.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/interior.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/grid.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/grid_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_building_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_line_pattern_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_line_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_point_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_polygon_pattern_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_polygon_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_raster_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_shield_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/grid/process_text_symbolizer.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/svg_output_grammars.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/svg_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/svg_generator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/svg_output_attributes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/process_symbolizers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/process_line_symbolizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/svg/output/process_polygon_symbolizer.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/libxml2_loader.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_arc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_arrowhead.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_bezier_arc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_bspline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_curves.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_embedded_raster_fonts.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_gsv_text.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_image_filters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_line_aa_basics.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_line_profile_aa.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_pixfmt_rgba.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_rounded_rect.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_sqrt_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_trans_affine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_trans_double_path.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_trans_single_path.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_trans_warp_magnifier.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_bspline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_contour.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_dash.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_markers_term.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_smooth_poly1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vcgen_stroke.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vpgen_clip_polygon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vpgen_clip_polyline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/agg/src/agg_vpgen_segmentator.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/geojson/geojson_datasource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/geojson/geojson_featureset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/geojson/geojson_index_featureset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/geojson/geojson_memory_index_featureset.cpp
 

  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/dbf_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/dbfile.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/shape_datasource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/shape_featureset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/shape_index_featureset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/shape_io.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/shape/shape_utils.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/raster/raster_datasource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/raster/raster_featureset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/raster/raster_info.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/generic_json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_geometry_to_geojson.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_feature_collection_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_feature_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_generator_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_geometry_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_geometry_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_json_positions_grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json/mapnik_topojson_grammar.cpp

  # ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/gdal/gdal_datasource.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/plugins/input/gdal/gdal_featureset.cpp
)

SET(ICU_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/external/icu/source/common/"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/external/icu/source/i18n/")

set(CMAKE_REQUIRED_DEFINITIONS -DBOOST_ALL_DYN_LINK -DBOOST_ALL_NO_LIB)
set(CMAKE_REQUIRED_INCLUDES ${Boost_INCLUDE_DIRS} ${ICU_INCLUDE_DIRS})

add_definitions(-DMAPNIK_EXPORTS)
add_definitions(-DHAVE_JPEG)
add_definitions(-DHAVE_PNG)
add_definitions(-DHAVE_WEBP)
add_definitions(-DMAPNIK_USE_PROJ4)
add_definitions(-DGRID_RENDERER)

add_definitions(-DMAPNIK_STATIC_PLUGINS)
add_definitions(-DMAPNIK_STATIC_PLUGIN_GEOJSON)
add_definitions(-DMAPNIK_STATIC_PLUGIN_SHAPE)
add_definitions(-DMAPNIK_STATIC_PLUGIN_RASTER)


add_library(mapnik STATIC ${mapnik_SOURCE_FILES})

target_link_libraries(mapnik ${mapnik_libraries})

TARGET_INCLUDE_DIRECTORIES(mapnik PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_SOURCE_FILES})
SOURCE_GROUP("include" FILES ${mapnik_HEADER_FILES})

SET_TARGET_PROPERTIES(mapnik
		                  PROPERTIES PUBLIC_HEADER "${headers}")

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(mapnik PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
