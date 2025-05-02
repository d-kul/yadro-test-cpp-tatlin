cmake_minimum_required(VERSION 3.28)
project(yadro-test-cpp-tatlin)

add_executable(main
  src/main.cpp)
target_include_directories(main PRIVATE src)
target_compile_features(main PRIVATE cxx_std_17)
