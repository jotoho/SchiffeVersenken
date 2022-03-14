cmake_minimum_required(VERSION 3.22)

execute_process(
    COMMAND git describe --tags --always --dirty
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_DESC_VER
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)

project(SchiffeVersenken HOMEPAGE_URL "https://github.com/jotoho/SchiffeVersenken")

set(SchiffeVersenken_VERSION "${GIT_DESC_VER}")
file(REMOVE "${CMAKE_SOURCE_DIR}/include/global-config.hpp")
configure_file(include/global-config.hpp.in "${CMAKE_SOURCE_DIR}/include/global-config.hpp")

add_executable(SchiffeVersenken src/main.cpp src/ai.cpp src/board-generator.cpp src/boardpoint.cpp src/gamelogic.cpp src/input.cpp src/output.cpp)
