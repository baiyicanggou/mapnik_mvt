INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/gdal")

set(mapnik_gdal_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/gdal/gdal_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/gdal/gdal_featureset.cpp"
)

ADD_LIBRARY(mapnik_gdal_input STATIC
            ${mapnik_gdal_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_gdal_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_gdal_input_SOURCE_FILES})
