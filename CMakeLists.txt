cmake_minimum_required(VERSION 3.12)
project(loggery)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)



include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/)

#set(FMT_SOURCE_FILES fmt/core.h fmt/format.cc fmt/format.h fmt/format-inl.h fmt/ostream.h fmt/posix.cc fmt/posix.h fmt/printf.h fmt/ranges.h fmt/time.h)


set(FMT_SOURCE_FILES external_libs/include/fmt/core.h external_libs/include/fmt/format.cc
    external_libs/include/fmt/format.h external_libs/include/fmt/format-inl.h external_libs/include/fmt/ostream.h
    external_libs/include/fmt/posix.cc external_libs/include/fmt/posix.h external_libs/include/fmt/printf.h
    external_libs/include/fmt/ranges.h external_libs/include/fmt/time.h)

set(IMGUI_SOURCE_FILES external_libs/include/imgui/imgui_impl_glfw.cpp
    external_libs/include/imgui/imgui_impl_opengl3.cpp
    external_libs/include/imgui/imgui.cpp external_libs/include/imgui/imgui_draw.cpp external_libs/include/imgui/imgui_demo.cpp
    external_libs/include/imgui/misc/stl/imgui_stl.cpp)

#set(GLFW_SOURCE_FILES external_libs/include/GLFW/glfw3.h external_libs/include/GLFW/glfw3native.h)

set(GLAD_SOURCE_FILES external_libs/include/glad/glad.c external_libs/include/glad/glad.h external_libs/include/glad/khrplatform.h )

set(SOURCE_FILES main.cpp content/files.h content/files_mapper.h src/classes/Image.cpp src/classes/Image.h src/classes/Vector.hpp
        src/classes/Color.hpp src/classes/Window.cpp src/classes/Window.h src/managers/ProgramManager.cpp src/managers/ProgramManager.h
        src/gui/Textbox.cpp src/gui/Textbox.h external_libs/include/cute_png.h src/classes/Timer.cpp src/classes/Timer.h src/gui/Text.cpp
        src/gui/Text.h src/managers/LogManager.cpp src/managers/LogManager.h src/forms/LogForm.cpp src/forms/LogForm.h src/forms/SystemLog.cpp
        src/forms/SystemLog.h src/gui/MenuBar.cpp src/gui/MenuBar.h src/gui/MenuItem.cpp src/gui/MenuItem.h)

add_executable(loggery ${SOURCE_FILES} ${FMT_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${GLAD_SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG 1)
else()
    set(RELEASE 1)
endif()

message("Is debug: ${DEBUG}")

if(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
elseif(APPLE)
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 1)
    set(MSVC 0)
    set(MINGW 0)
elseif(WIN32)
    set(LINUX 0)
    set(WINDOWS 1)
    set(APPLE 0)
    if(MSVC)
        set(MSVC 1)
        set(MINGW 0)
    elseif(MINGW)
        set(MINGW 1)
        set(MSVC 0)
    endif()
else()
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
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
elseif(APPLE)
    message("Using MAC")
    if(DEBUG)
        message(WARN "CLANG-DEBUG")
        set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/osx/debug/libglfw3.a ${PROJECT_SOURCE_DIR}/external_libs/lib/osx/debug/libclip.a)
        set(GLFW_DEPENDENCIES /System/Library/Frameworks/Cocoa.framework /System/Library/Frameworks/OpenGL.framework /System/Library/Frameworks/IOKit.framework /System/Library/Frameworks/CoreVideo.framework)#-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo)
        target_link_libraries(loggery /usr/local/opt/llvm/lib/libc++experimental.a ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
    else()
        message("CLANG-RELEASE")
        set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/osx/release/libglfw3.a ${PROJECT_SOURCE_DIR}/external_libs/lib/osx/release/libclip.a)
        set(GLFW_DEPENDENCIES /System/Library/Frameworks/Cocoa.framework /System/Library/Frameworks/OpenGL.framework /System/Library/Frameworks/IOKit.framework /System/Library/Frameworks/CoreVideo.framework)#-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo)
        target_link_libraries(loggery /usr/local/opt/llvm/lib/libc++experimental.a ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
    endif()
elseif(WINDOWS)
    message(WARNING "Using WINDOWS")
    if(MSVC)
        message("Compiler: MSVC")
        if(DEBUG)
            message(WARN "MSVC-DEBUG")
            set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/win/msvc/debug/glfw3.lib ${PROJECT_SOURCE_DIR}/external_libs/lib/win/msvc/debug/clip.lib)
            set(GLFW_DEPENDENCIES )
            target_link_libraries(loggery ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
        else()
            message("MSVC-RELEASE")
            set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/win/msvc/release/glfw3.lib ${PROJECT_SOURCE_DIR}/external_libs/lib/win/msvc/release/clip.lib)
            set(GLFW_DEPENDENCIES )
            target_link_libraries(loggery ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
        endif()
    elseif(MINGW)
        message(WARNING "Compiler: MinGW")
        if(DEBUG)
            message(WARN "MinGW-DEBUG")
            set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/win/mingw/debug/libglfw3.a ${PROJECT_SOURCE_DIR}/external_libs/lib/win/mingw/debug/libclip.a)
            set(GLFW_DEPENDENCIES stdc++fs)
            target_link_libraries(loggery ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
        else()
            message("MinGW-RELEASE")
            set(MY_STATIC_LIBS ${PROJECT_SOURCE_DIR}/external_libs/lib/win/mingw/release/libglfw3.a ${PROJECT_SOURCE_DIR}/external_libs/lib/win/mingw/release/libclip.a)
            set(GLFW_DEPENDENCIES stdc++fs)
            target_link_libraries(loggery ${MY_STATIC_LIBS} ${GLFW_DEPENDENCIES})
        endif()
    else()
        message(WARNING "Compiler: UNKNOWN")
    endif()
endif()

add_subdirectory(tests)