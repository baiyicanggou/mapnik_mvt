INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/geojson")

set(mapnik_geojson_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/geojson/geojson_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/geojson/geojson_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/geojson/geojson_index_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/geojson/geojson_memory_index_featureset.cpp"
)

ADD_LIBRARY(mapnik_geojson_input STATIC
            ${mapnik_geojson_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_geojson_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_geojson_input_SOURCE_FILES})
