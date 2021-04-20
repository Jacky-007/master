cmake_minimum_required(VERSION 3.0.0)

project(Lab6.Clipping)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
    message( FATAL_ERROR "该项目只能在Windows环境下配置和运行")
endif()

set(HEADERS basewin.hpp geometry.hpp graphics.hpp memdc.hpp)
set(SOURCES main.cpp geometry.cpp graphics.cpp)

add_executable(Clipping ${SOURCES} ${HEADERS})
add_executable(vector_test transform.cpp graphics.cpp geometry.cpp)

set_target_properties(Clipping PROPERTIES LINK_OPTIONS "/SUBSYSTEM:WINDOWS")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
