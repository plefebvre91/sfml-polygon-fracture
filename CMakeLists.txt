project(Fracture)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic --std=c++17")

set(SRC_FILES main.cpp fracturable.cpp utils.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

link_libraries(sfml-graphics sfml-window sfml-system -ltbb)

add_executable(fracture ${SRC_FILES})
