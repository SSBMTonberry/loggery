cmake_minimum_required(VERSION 3.12)
project(loggery)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/)

#set(FMT_SOURCE_FILES fmt/core.h fmt/format.cc fmt/format.h fmt/format-inl.h fmt/ostream.h fmt/posix.cc fmt/posix.h fmt/printf.h fmt/ranges.h fmt/time.h)
set(SOURCE_FILES main.cpp content/files.h content/files_mapper.h)

set(FMT_SOURCE_FILES external_libs/include/fmt/core.h external_libs/include/fmt/format.cc
    external_libs/include/fmt/format.h external_libs/include/fmt/format-inl.h external_libs/include/fmt/ostream.h
    external_libs/include/fmt/posix.cc external_libs/include/fmt/posix.h external_libs/include/fmt/printf.h
    external_libs/include/fmt/ranges.h external_libs/include/fmt/time.h)

set(IMGUI_SOURCE_FILES external_libs/include/imgui/imgui_impl_glfw.cpp
    external_libs/include/imgui/imgui_impl_opengl3.cpp
    external_libs/include/imgui/imgui.cpp external_libs/include/imgui/imgui_draw.cpp external_libs/include/imgui/imgui_demo.cpp)

#set(GLFW_SOURCE_FILES external_libs/include/GLFW/glfw3.h external_libs/include/GLFW/glfw3native.h)

set(GLAD_SOURCE_FILES external_libs/include/glad/glad.c external_libs/include/glad/glad.h external_libs/include/glad/khrplatform.h external_libs/include/cute_png.h src/classes/Image.cpp src/classes/Image.h src/classes/Vector.hpp src/classes/Color.hpp src/classes/Window.cpp src/classes/Window.h src/managers/ProgramManager.cpp src/managers/ProgramManager.h)

add_executable(loggery ${SOURCE_FILES} ${FMT_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${GLAD_SOURCE_FILES})

set(LINUX 0)
set(WINDOWS 0)
set(APPLE 0)
set(MSVC 0)
set(MINGW 0)
if(UNIX AND NOT APPLE)
    set(LINUX 1)
elseif(APPLE)
    set(APPLE 1)
elseif(WIN32)
    set(WINDOWS 1)
    if(MSVC)
        set(MSVC 1)
    elseif(MINGW)
        set(MINGW 1)
    endif()
endif()

configure_file (
        "${PROJECT_SOURCE_DIR}/LoggeryConfig.h.in"
        "${PROJECT_SOURCE_DIR}/LoggeryConfig.h"
)


if(LINUX)
    set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/linux/libglfw3.a ${PROJECT_SOURCE_DIR}/external_libs/lib/linux/libclip.a)
    #set(GLFW_DEPENDENCIES -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp)
    set(GLFW_DEPENDENCIES -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -ldl -lXxf86vm -lX11 -lpthread)
    target_link_libraries(loggery stdc++fs ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
elseif(WINDOWS)
    message("Using WINDOWS")
    if(MSVC)
        message("Compiler: MSVC")
        if(DEBUG)
            message("MSVC-DEBUG")
        else()
            message("MSVC-RELEASE")
        endif()
    elseif(MINGW)
        message("Compiler: MinGW")
    else()
        message("Compiler: UNKNOWN")
    endif()
endif()