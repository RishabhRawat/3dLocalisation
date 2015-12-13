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
#file(GLOB SOURCES "src/Tests/marchingCubesTest.cpp")


set(SOURCES ${SOURCES} ${TARGETFILE})

project (3dLocalisation)
add_executable(3dLocalisation ${SOURCES})

## Link libraries
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(OPENCV REQUIRED opencv)

include_directories(include ${GLFW_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
target_link_libraries(3dLocalisation ${GLFW} ${CMAKE_DL_LIBS} ${GLFW_LIBRARIES} ${OPENCV_LIBRARIES})