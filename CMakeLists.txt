cmake_minimum_required(VERSION 2.8)

project(craft)

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
include_directories(deps/glew/include)
include_directories(deps/glfw/include)

add_executable(
    sample2
    sample_gl2.cpp
    imgui.cpp
    imguiRenderGL2.cpp
    deps/glew/src/glew.c
)
add_executable(
    sample3
    sample_gl3.cpp
    imgui.cpp
    imguiRenderGL3.cpp
    deps/glew/src/glew.c
)

if(APPLE)
    target_link_libraries(sample2 glfw ${GLFW_LIBRARIES})
    target_link_libraries(sample3 glfw ${GLFW_LIBRARIES})
endif()

if(UNIX)
    target_link_libraries(sample2 dl glfw ${GLFW_LIBRARIES})
    target_link_libraries(sample3 dl glfw ${GLFW_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(sample2 ws2_32.lib glfw ${GLFW_LIBRARIES})
    target_link_libraries(sample3 ws2_32.lib glfw ${GLFW_LIBRARIES})
endif()
