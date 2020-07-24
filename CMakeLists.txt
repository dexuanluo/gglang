cmake_minimum_required(VERSION 3.14)
project(gg_lang)

set(CMAKE_CXX_STANDARD 17)

add_executable(gg_lang main.cpp src/lexer.h src/parser.h src/ErrorObserver.h src/token.h src/node.h)