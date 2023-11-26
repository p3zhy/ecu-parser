cmake_minimum_required(VERSION 3.10)
project(ecu-parser)
set(CMAKE_C_STANDARD 11)
include_directories(inc)

# Source files
set(SOURCES
    src/ecu_parser.c
    src/obd2.c
    src/uds.c
    main.c
)

add_executable(ecutool ${SOURCES})