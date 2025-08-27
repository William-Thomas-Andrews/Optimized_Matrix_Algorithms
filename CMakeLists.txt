cmake_minimum_required(VERSION 4.1.0)

project(OPT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(TBB REQUIRED)

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

add_executable(OPT 
    test/Test.cpp
    ${SRC_FILES}
)

target_include_directories(SPG
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC ${CMAKE_SOURCE_DIR}/src/utils
    PUBLIC ${CMAKE_SOURCE_DIR}/src/graph
    PUBLIC ${CMAKE_SOURCE_DIR}/src/data
)

target_link_libraries( OPT
    PUBLIC TBB                    # Here, for access without relying on the submodule, instead of <folly> write <Folly::folly>
)