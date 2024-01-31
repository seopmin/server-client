cmake_minimum_required(VERSION 3.16)

project(
    minseop  
    VERSION 1.0.0       
    LANGUAGES C CXX     
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF) 

find_package(Boost 1.84.0 REQUIRED COMPONENTS system regex thread)
include_directories(${Boost_INCLUDE_DIRS})

set(EXECUTABLE_NAME exe)

add_subdirectory(app)
# add_subdirectory(src)
