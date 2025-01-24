cmake_minimum_required(VERSION 3.15)

project(deepthought)

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

add_executable(deepthought src/main.cpp src/DeepThoughtError.cpp src/DeepThought.cpp)

target_link_libraries(deepthought ${CONAN_LIBS})

find_package(GTest REQUIRED)
target_link_libraries(deepthought GTest::GTest)

target_include_directories(deepthought PRIVATE src)