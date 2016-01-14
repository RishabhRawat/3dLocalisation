cmake_minimum_required(VERSION 3.0.0)

#set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.c*")
file(GLOB SHADERS "shaders/*.*")
file(COPY ${SHADERS} DESTINATION ".")


project (3dLocalisation)
add_executable(3dLocalisation ${SOURCES})

set(debug "-g -O0")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings} ${debug}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++11 ${debug}")


## Link libraries
find_package(PkgConfig REQUIRED)
find_package(X11 REQUIRED)
find_package (Threads REQUIRED)
find_package(PNG REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(include)
target_link_libraries(3dLocalisation  ${PNG_LIBRARIES} ${GLFW_LIBRARIES}  ${X11_X11_LIB} ${X11_Xinerama_LIB} ${X11_Xcursor_LIB} 
	 ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${CMAKE_THREAD_LIBS_INIT} ${X11_Xinput_LIB} ${CMAKE_DL_LIBS})
