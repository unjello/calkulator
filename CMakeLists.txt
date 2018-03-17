cmake_minimum_required(VERSION 3.2)
project(calkulator)

enable_testing()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE contrib/Catch/single_include)

add_library(SpdLog INTERFACE)
target_include_directories(SpdLog INTERFACE contrib/spdlog/include)

add_subdirectory(core)
