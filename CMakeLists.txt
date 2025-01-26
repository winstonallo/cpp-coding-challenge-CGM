cmake_minimum_required(VERSION 3.15)

project(deepthought)

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

add_executable(deepthought src/main.cpp src/DeepThoughtError.cpp)
target_link_libraries(deepthought ${CONAN_LIBS})

find_package(GTest REQUIRED)
add_executable(tests test/tests.cpp src/DeepThoughtError.cpp)
target_link_libraries(tests GTest::GTest GTest::Main ${CONAN_LIBS})

target_include_directories(deepthought PRIVATE src)
target_include_directories(tests PRIVATE src)

target_compile_options(deepthought PRIVATE -Wall -Wextra -Werror -O3)