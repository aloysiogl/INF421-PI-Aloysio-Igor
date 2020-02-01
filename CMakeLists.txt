PROJECT(TWO_CENTERS)
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

add_library(lib Edge.cpp Arrow.cpp Tree.cpp)
add_executable(main main.cpp)
target_link_libraries(main lib)