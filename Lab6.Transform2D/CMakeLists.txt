cmake_minimum_required(VERSION 3.0.0)

project(Lab4.Geometry2D)

if(NOT WIN32)
    message( FATAL_ERROR "该项目只能在Windows环境下配置和运行")
endif()

set(HEADERS basewin.hpp geometry.hpp memdc.hpp)
set(SOURCES main.cpp geometry.cpp)

add_executable(Transform2D ${SOURCES} ${HEADERS})
add_executable(matrix_test transform.cpp geometry.cpp geometry.hpp)

set_target_properties(Transform2D PROPERTIES LINK_OPTIONS "/SUBSYSTEM:WINDOWS")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
