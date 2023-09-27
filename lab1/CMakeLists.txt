cmake_minimum_required(VERSION 3.26)
project(lab1)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Find the necessary OpenGL and GLUT packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Include OpenGL and GLUT headers
include_directories(${GLUT_INCLUDE_DIRS})

# Add the executable and link libraries
add_executable(lab1 Pontok.cpp)

# Link OpenGL and GLUT libraries
target_link_libraries(lab1 OpenGL::GL OpenGL::GLU ${GLUT_LIBRARIES})
