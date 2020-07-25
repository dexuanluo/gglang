cmake_minimum_required(VERSION 3.14)
project(gg_lang)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/main)
include_directories(src/object)
include_directories(src/object/utils)

add_executable(gg_lang
        src/main/executor.h
        src/main/lexer.h
        src/main/parser.h
        src/object/utils/excalibur.h
        src/object/node.h
        src/object/token.h
        main.cpp src/object/gg_object.h src/object/utils/gg_memory.h)
