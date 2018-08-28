cmake_minimum_required(VERSION 3.12)
project(test_loggery)

include_directories(${PROJECT_SOURCE_DIR}../src ${PROJECT_SOURCE_DIR}../external_libs/include)
message("Test dir" ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES test_misc.cpp ../src/classes/Timer.cpp)

add_executable(test_loggery ${SOURCE_FILES})