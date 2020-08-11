find_package(Boost REQUIRED COMPONENTS)

enable_testing()

add_executable(my_algorithm_test
  sort.cc)
target_link_libraries(my_algorithm_test gtest gtest_main)
message("${PROJECT_SOURCE_DIR}")
target_include_directories(my_algorithm_test SYSTEM
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_test(my_algorithm_test_all my_algorithm_test)
