project(Lab2.HelloTriangle)
set(target_name HelloTriangle)

if(APPLE)
    find_library(glfw3_libs NAMES libglfw3 glfw3 HINTS ${External_Deps_Dir}/glfw/lib-universal)
    message("link directry at ${External_Deps_Dir}/glfw/lib-universal with ${glfw3_libs}")
elseif(MSVC)
	if(MSVC_VERSION EQUAL 1600)
		find_library(glfw3_libs NAMES libglfw3 glfw3 HINTS ${External_Deps_Dir}/glfw/lib-vc2010)
	else()
		find_library(glfw3_libs NAMES libglfw3 glfw3 HINTS ${External_Deps_Dir}/glfw/lib-vc2015)
	endif()
	message("link directry at ${External_Deps_Dir}/glfw/lib with ${glfw3_libs}")
elseif(UNIX)
# install libglfw3-dev manually on UNIX
    set(glfw3_libs glfw)
endif()

set(HEADERS helper.h) 
set(SOURCES main.cpp helper.cpp)
set(LIBS glad ${glfw3_libs})

add_executable(${target_name} ${HEADERS} ${SOURCES})
target_link_libraries(${target_name} PRIVATE ${LIBS})

