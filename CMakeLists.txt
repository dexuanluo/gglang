cmake_minimum_required(VERSION 3.14)
project(gg_lang)

set(CMAKE_CXX_STANDARD 17)

add_executable(gg_lang main.cpp src/main/lexer.h src/main/parser.h src/object/utils/excalibur.h src/object/token.h src/object/node.h src/main/executor.h)