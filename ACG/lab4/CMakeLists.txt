cmake_minimum_required(VERSION 3.8)
project(lab4)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp src/point/Point.cpp src/point/Point.h src/buffer/Buffer.cpp src/buffer/Buffer.h src/plane/Plane.cpp src/plane/Plane.h src/plane/Line.cpp src/plane/Line.h)
add_executable(lab4 ${SOURCE_FILES})
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(lab4 ${SDL2_LIBRARIES})
