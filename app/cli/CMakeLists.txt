cmake_minimum_required(VERSION 3.2)
project(calkulator-cli)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

add_executable(cli
  main.cpp)

target_link_libraries(cli SpdLog)