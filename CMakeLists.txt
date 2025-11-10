cmake_minimum_required(VERSION 3.16)

project(NewtonFractal_ISPC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(ISPC_EXECUTABLE ispc REQUIRED)

set(NEWTON_ISPC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/newton.ispc)
set(NEWTON_ISPC_O   ${CMAKE_CURRENT_BINARY_DIR}/newton_ispc.o)
set(NEWTON_ISPC_H   ${CMAKE_CURRENT_BINARY_DIR}/newton_ispc.h)

add_custom_command(
        OUTPUT  ${NEWTON_ISPC_O} ${NEWTON_ISPC_H}
        COMMAND ${ISPC_EXECUTABLE}
        ${NEWTON_ISPC_SRC}
        -O2
        -o ${NEWTON_ISPC_O}
        -h ${NEWTON_ISPC_H}
        DEPENDS ${NEWTON_ISPC_SRC}
        COMMENT "Compiling ISPC file newton.ispc"
        VERBATIM
)

set_source_files_properties(${NEWTON_ISPC_O}
        PROPERTIES
        EXTERNAL_OBJECT TRUE
        GENERATED TRUE
)

add_executable(NewtonFractal_ISPC
        main.cpp
        image_io.cpp
        ${NEWTON_ISPC_O}
)

target_include_directories(NewtonFractal_ISPC PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
