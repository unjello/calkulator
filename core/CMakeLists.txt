cmake_minimum_required(VERSION 3.3)
project(core CXX)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

add_library(core_lib
  include/core/Engine.h
  src/Engine.cpp
  )

find_package(Boost 1.61.0 REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

target_include_directories(core_lib PUBLIC include)
target_include_directories(core_lib PRIVATE src)
target_link_libraries(core_lib SpdLog)

if(BUILD_SHARED_LIBS)
 target_compile_definitions(core_lib PRIVATE CORE_EXPORTS)
 target_compile_definitions(core_lib INTERFACE CORE_IMPORTS)
endif()

add_executable(core_test test/CoreLibTest.cpp test/EngineTest.cpp)
target_link_libraries(core_test Catch)
target_link_libraries(core_test core_lib)

add_test(NAME CoreTest COMMAND core_test)