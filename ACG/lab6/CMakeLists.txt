cmake_minimum_required(VERSION 3.8)
project(lab6)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(lab6 ${SOURCE_FILES})

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries(lab6 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )

# sudo apt-get install libxmu-dev libxi-dev
# sudo apt-get install freeglut3-dev