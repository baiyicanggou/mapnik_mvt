INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/postgis")

set(mapnik_postgis_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/postgis/postgis_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/postgis/postgis_featureset.cpp"
)

ADD_LIBRARY(mapnik_postgis_input STATIC
            ${mapnik_postgis_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_postgis_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_postgis_input_SOURCE_FILES})
