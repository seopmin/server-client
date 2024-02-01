cmake_minimum_required(VERSION 3.16)

project(
    minseop  
    VERSION 1.0.0       
    LANGUAGES C CXX     
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF) 


if(UNIX AND NOT APPLE)  # Ubuntu
    find_package(Boost 1.84.0 REQUIRED COMPONENTS system regex thread)
elseif(APPLE)  # macOS
    find_package(Boost REQUIRED)
endif()


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME exe)


add_subdirectory(app)
add_subdirectory(src/lib)
