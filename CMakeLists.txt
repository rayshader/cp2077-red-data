cmake_minimum_required(VERSION 3.27)
project(RedData VERSION 0.4.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(RedData INTERFACE)
target_compile_definitions(RedData INTERFACE HAS_REDDATA)
target_include_directories(RedData INTERFACE include)
