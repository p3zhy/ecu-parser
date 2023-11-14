cmake_minimum_required(VERSION 3.10)
project(ecu-parser)

set(CMAKE_C_STANDARD 11)

add_executable(ecutool src/main.c src/ecu_parser.c)

# TODO: Add any necessary include directories or link libraries
