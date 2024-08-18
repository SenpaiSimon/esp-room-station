cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

IF(DEFINED ENV{IDF_PATH})
    execute_process(COMMAND get_idf)
ENDIF()

set(EXTRA_COMPONENT_DIRS components)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp-room-station)