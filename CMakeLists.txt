cmake_minimum_required(VERSION 3.11)
project(my-algorithm)

set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(test)
