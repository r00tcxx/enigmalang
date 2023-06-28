project(el)

include_directories(${CMAKE_SOURCE_DIR}/src)

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

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "/SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$(Configuration)/"
)
