cmake_minimum_required(VERSION 2.8)

project(imgui)

if (CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    if(MSVC)
#        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        add_definitions(/Zi /Oy- /DDEBUG)
    else()
        add_definitions(-std=c99 -O0 -DDEBUG -D_DEBUG)
    endif()
else()
    if(MSVC)
#        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        add_definitions(/Ox /Oy /DNDEBUG /D_NDEBUG)
    else()
        add_definitions(-std=c99 -O3 -DNDEBUG -D_NDEBUG)
    endif()
endif()

add_subdirectory(deps/glfw)
include_directories(src)
include_directories(deps/glew/include)
include_directories(deps/glfw/include)

add_executable(
    sample
    sample/sample.cc
    src/imgui.cpp
    src/imguiGL.cpp
    src/fonts/Entypo-Social.ttf.cpp
    src/fonts/Entypo.ttf.cpp
    src/fonts/Ubuntu-B.ttf.cpp
    src/stb_image.c
    deps/glew/src/glew.c
)

if(APPLE)
    target_link_libraries(sample glfw ${GLFW_LIBRARIES})
endif()

if(UNIX)
    target_link_libraries(sample dl glfw ${GLFW_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(sample ws2_32.lib glfw ${GLFW_LIBRARIES})
endif()
