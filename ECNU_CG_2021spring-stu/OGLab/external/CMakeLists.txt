project(OGLab_External) 

# add_subdirectory(eigen3)
if(UNIX) 
    add_subdirectory(glfw)
endif()

add_subdirectory(glad)