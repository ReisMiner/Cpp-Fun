cmake_minimum_required(VERSION 3.19)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp main.cpp)
add_executable(cpp2 noVirus.cpp)
target_link_libraries(cpp -static-libgcc -static-libstdc++)
