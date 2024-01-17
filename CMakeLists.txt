cmake_minimum_required(VERSION 3.12)
project(university-tree-data-structures)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(benchmark)
add_subdirectory(implementation)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cc)
target_link_libraries(${PROJECT_NAME} benchmark implementation)
target_compile_options(${PROJECT_NAME}
    PRIVATE
         $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>: 
         -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy
         -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs
         -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo
         -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-variable>

         $<$<CXX_COMPILER_ID:GNU>: -Wlogical-op -Wnoexcept -Wstrict-null-sentinel>
)