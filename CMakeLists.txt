cmake_minimum_required(VERSION 3.0.0)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

set(debug, "-g -O0")

set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} ${warnings} ${debug}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${warnings} ${debug}")

set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")


file(GLOB SOURCES "src/*.c*")
file(GLOB TARGETFILE "src/Tests/marchingCubesTest.cpp")
file(GLOB SHADERS "shaders/*.*")
file(COPY ${SHADERS} DESTINATION ".")
#file(GLOB SOURCES "src/Tests/marchingCubesTest.cpp")


set(SOURCES ${SOURCES} ${TARGETFILE})

project (3dLocalisation)
add_executable(3dLocalisation ${SOURCES})

## Link libraries
find_package(PkgConfig REQUIRED)
find_package(X11 REQUIRED)
find_package (Threads REQUIRED)
#find_package(glbinding REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

#pkg_search_module(OPENCV REQUIRED opencv)

include_directories(include ${GLFW_INCLUDE_DIRS})
target_link_libraries(3dLocalisation  ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${X11_X11_LIB} ${X11_Xinerama_LIB} ${X11_Xcursor_LIB} 
	 ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${CMAKE_THREAD_LIBS_INIT} ${X11_Xinput_LIB} ${CMAKE_DL_LIBS})
