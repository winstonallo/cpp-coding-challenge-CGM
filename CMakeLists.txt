cmake_minimum_required(VERSION 3.15)

project(deepthought)

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

add_executable(deepthought src/main.cpp)

target_link_libraries(deepthought ${CONAN_LIBS})

find_package(gtest REQUIRED)
target_link_libraries(deepthought gtest::gtest)