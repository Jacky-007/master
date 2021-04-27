cmake_minimum_required(VERSION 3.16.0)
project(OpenGL_Lab VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

# move output folder to bin
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

if(NOT MSVC)
    set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
endif()

set(External_Deps_Dir ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(Projects_Dir ${CMAKE_CURRENT_SOURCE_DIR}/projects)

add_subdirectory(external)
add_subdirectory(projects)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
