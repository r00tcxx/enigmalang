project(el)

file(GLOB_RECURSE SRC
    *.h
    *.hpp
    *.cpp
    *.c
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "source" FILES ${SRC})

add_executable(
    ${PROJECT_NAME}
    WIN32
    ${SRC}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$(Configuration)/bin")