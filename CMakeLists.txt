cmake_minimum_required(VERSION 3.12)
project(university-tree-data-structures)

add_subdirectory(benchmark)
add_subdirectory(implementation)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cc)
target_link_libraries(${PROJECT_NAME} benchmark implementation)