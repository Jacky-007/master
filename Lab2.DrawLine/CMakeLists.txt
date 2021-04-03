
project(Lab1_DrawLine)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else(WIN32)
    message( FATAL_ERROR "该项目只能在Windows环境下配置和运行")
endif(WIN32)


add_executable(DrawLine main.cpp line.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


