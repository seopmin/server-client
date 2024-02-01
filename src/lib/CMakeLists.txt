set(LIBRARY_SOURCES
  "empty_source_file.cc")
set(LIBRARY_HEADERS
  # "net_common.hpp"
  # "net_message.hpp"
  "olc_net.hpp")

set(LIBRARY_INCLUDES
  "./")

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SOURCES}
  ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC 
  ${LIBRARY_INCLUDES})

target_link_libraries(${LIBRARY_NAME} PUBLIC
  ${Boost_LIBRARIES})
