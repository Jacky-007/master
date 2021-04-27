project(glad)
include_directories(include)
add_library(glad STATIC src/glad.c)

if (UNIX) 
    target_link_libraries(glad dl)
endif()