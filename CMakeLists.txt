#Author Camilo Talero

cmake_minimum_required(VERSION 3.5)

project(Nyx)

set(CMAKE_BINARY_DIR .)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "-Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )

SET(CMAKE_CXX_FLAGS "-std=c++1y -g -fopenmp")

#Every site says this should not be done so be very careful
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" 
    "${PROJECT_SOURCE_DIR}/*.hpp")
add_executable(Nyx ${SOURCES})

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Helpers")
include_directories("${PROJECT_SOURCE_DIR}/Nyx")
include_directories("${PROJECT_SOURCE_DIR}/Nyx/Nyx-Window")
include_directories("${PROJECT_SOURCE_DIR}/Helios")
include_directories("${PROJECT_SOURCE_DIR}/Helios/OpenGL-Wrappers")
include_directories("${PROJECT_SOURCE_DIR}/Helios/Debugging")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})
target_link_libraries(Nyx glfw GL GLEW freetype pthread)

file(COPY ${PROJECT_SOURCE_DIR}/Helios/Helios-Shaders DESTINATION ${CMAKE_BINARY_DIR})