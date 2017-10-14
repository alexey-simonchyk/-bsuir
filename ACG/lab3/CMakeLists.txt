cmake_minimum_required(VERSION 3.8)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

set(SOURCE_FILES main.cpp src/Rectangle.cpp src/Rectangle.h src/Point.cpp src/Point.h)
add_executable(lab3 ${SOURCE_FILES})
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(lab3 ${SDL2_LIBRARIES})
