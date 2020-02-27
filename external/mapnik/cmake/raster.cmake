INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/raster")

set(mapnik_raster_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/raster/raster_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/raster/raster_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/raster/raster_info.cpp"
)

ADD_LIBRARY(mapnik_raster_input STATIC
            ${mapnik_raster_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_raster_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_raster_input_SOURCE_FILES})
