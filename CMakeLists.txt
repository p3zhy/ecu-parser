cmake_minimum_required(VERSION 3.10)
project(ecu-parser)
set(CMAKE_C_STANDARD 11)
include_directories(inc)

# Source files
set(SOURCES
    src/ecu_parser.c
    src/obd2.c
    src/uds.c
    src/j1939.c
    src/helpers.c
    main.c
)

add_executable(ecutool ${SOURCES})

# Link with the math library
target_link_libraries(ecutool m)