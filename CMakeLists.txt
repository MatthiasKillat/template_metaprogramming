cmake_minimum_required(VERSION 3.10)
project(concurrency_primitives )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( include )

FILE(GLOB SOURCES "*.cpp")

add_executable(sfinae
  main.cpp
)

#target_link_libraries(sfinae)


