cmake_minimum_required(VERSION 3.0.0)

project(Lab7.Curve)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
    message( FATAL_ERROR "该项目只能在Windows环境下配置和运行")
endif()

# include_directories(imgui)
# file(GLOB_RECURSE Curve_Externals "imgui/*.h" "imgui/*.cpp")
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Curve_Externals})

set(HEADERS basewin.hpp geometry.hpp graphics.hpp memdc.hpp)
set(SOURCES main.cpp geometry.cpp graphics.cpp)

add_executable(Curve ${SOURCES} ${HEADERS} ${Curve_Externals})

set_target_properties(Curve PROPERTIES LINK_OPTIONS "/SUBSYSTEM:WINDOWS")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
