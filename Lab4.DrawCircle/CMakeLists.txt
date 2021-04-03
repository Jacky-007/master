cmake_minimum_required(VERSION 3.0.0)

project(Lab3.DrawEllipse)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else(WIN32)
    message( FATAL_ERROR "该项目只能在Windows环境下配置和运行")
endif(WIN32)

set(HEADERS basewin.hpp geometry.hpp)
set(SOURCES main.cpp geometry.cpp)

add_executable(DrawBoard ${SOURCES} ${HEADERS})

set_target_properties(DrawBoard PROPERTIES LINK_OPTIONS "/SUBSYSTEM:WINDOWS")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
