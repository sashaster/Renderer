cmake_minimum_required(VERSION 4.1)
project(Renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(VENV_DIR ${CMAKE_BINARY_DIR}/.venv)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

if(NOT EXISTS ${VENV_DIR})
    message(STATUS "Creating virtual environment... ")
    execute_process(COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR})
endif()
set(ENV{VIRTUAL_ENV} ${VENV_DIR})
set(Python3_FIND_VIRTUALENV ONLY)

if(WIN32)
    set(VENV_PYTHON ${VENV_DIR}/Scripts/python.exe)
else()
    set(VENV_PYTHON ${VENV_DIR}/bin/python3)
endif()

execute_process(COMMAND ${VENV_PYTHON} -m pip install --quiet jinja2)

file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Resources/*")

#Copy resources to the binary folder
add_custom_command(
        OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/copied.stamp"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/Resources"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources"
        COMMAND "${CMAKE_COMMAND}" -E touch "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/copied.stamp"
        DEPENDS ${RESOURCES}
        COMMENT "Copying resources..."
)
add_subdirectory(core)
add_subdirectory(app)

add_custom_target(copy_resources ALL DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/copied.stamp")
add_dependencies(renderer copy_resources)
