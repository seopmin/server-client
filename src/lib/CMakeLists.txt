set(LIBRARY_SOURCES
  "empty_source_file.cc")
set(LIBRARY_HEADERS
  "olc_net.h")

set(LIBRARY_INCLUDES
  "./")

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SOURCES}
  ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC 
  ${LIBRARY_INCLUDES})

target_link_libraries(${LIBRARY_NAME} PUBLIC
  ${Boost_LIBRARIES})
