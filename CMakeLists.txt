cmake_minimum_required(VERSION 3.28)
project(yadro-test-cpp-tatlin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main
  src/Solution.cpp
  src/main.cpp)
target_include_directories(main PRIVATE src)
target_compile_features(main PRIVATE cxx_std_17)

enable_testing()

add_executable(solution_test
  src/Solution.cpp
  test/test.cpp)
target_link_libraries(solution_test GTest::gtest_main)
target_include_directories(solution_test PRIVATE src)

include(GoogleTest)
gtest_discover_tests(solution_test)
