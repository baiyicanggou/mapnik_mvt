INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/pgraster")

set(mapnik_pgraster_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/pgraster/pgraster_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/pgraster/pgraster_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/pgraster/pgraster_wkb_reader.cpp"
)

ADD_LIBRARY(mapnik_pgraster_input STATIC
            ${mapnik_pgraster_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_pgraster_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_pgraster_input_SOURCE_FILES})
