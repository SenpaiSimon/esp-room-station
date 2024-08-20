cmake_minimum_required(VERSION 3.8)
# set(CMAKE_CXX_STANDARD 17)

IF(NOT DEFINED ENV{IDF_TOOLS_PY_PATH})
    IF(WIN32)
        execute_process(COMMAND cmd /c "%ESP_OWN_PATH%/esp-idf/export.bat")
    ELSE()
        execute_process(COMMAND get_idf)
    ENDIF()
ENDIF()


# set(EXTRA_COMPONENT_DIRS components)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp-room-station)