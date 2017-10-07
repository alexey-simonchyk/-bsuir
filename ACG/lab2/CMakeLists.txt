cmake_minimum_required(VERSION 3.9)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}\\lib\\i686-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(lab2 ${SOURCE_FILES})

target_link_libraries(lab2 ${SDL2_LIBRARY})

# Add to classpath MinGw/bin folder
# Copy SDL2.dll and sdl2-config to MinGw/bin folder
# Copy i686-w64-mingw32 to project-dir/lib folde