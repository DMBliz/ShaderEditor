project(shaderEditor)
cmake_minimum_required(VERSION 3.18)
SET(CMAKE_CXX_STANDARD 17)
set(GLFW_STATIC 1)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)

add_subdirectory(vendor/glfw)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imnodes/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/include")


list(APPEND SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imnodes/imnodes.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/stb_image.h"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/common.h"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/nfd_common.c"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/nfd_common.h"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/simple_exec.h"
"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Render.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Render.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Generator.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Generator.h"
"${CMAKE_CURRENT_SOURCE_DIR}/NodeLibrary.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/NodeLibrary.h"
"${CMAKE_CURRENT_SOURCE_DIR}/App.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/App.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Utils.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Graph.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Graph.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Serialization.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Serialization.h"
"${CMAKE_CURRENT_SOURCE_DIR}/IdProvider.h"
"${CMAKE_CURRENT_SOURCE_DIR}/IdProvider.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/FileSerialization.h"
"${CMAKE_CURRENT_SOURCE_DIR}/xmath.h")

if(WIN32)
    add_definitions(-DWIN32)
    list(APPEND libs glfw gdi32 user32 kernel32 OpenGL32.lib)
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/nfd_win.cpp")
elseif(APPLE) #mac os
    add_definitions(-DOSX)
    list(APPEND libs 
        "glfw"
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/nfd_cocoa.m")
elseif(UNIX AND NOT APPLE) #linux
    add_definitions(-DLINUX)
    list(APPEND libs glfw "GL" "X11" "Xrandr" "pthread" "Xi")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/nativefiledialog/src/nfd_gtk.c")
endif()

add_subdirectory(vendor/glm)
list(APPEND libs glm)

add_executable(shaderEditor ${SOURCES} ${resources})

target_link_libraries(shaderEditor ${libs})

