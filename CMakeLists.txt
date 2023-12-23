cmake_minimum_required(VERSION 3.12)
project(university-tree-data-structures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(benchmark)
add_subdirectory(implementation)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cc)
target_link_libraries(${PROJECT_NAME} benchmark implementation)