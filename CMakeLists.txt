cmake_minimum_required(VERSION 3.15)

project(CGM)

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

add_executable(CGM src/main.cpp)

target_link_libraries(CGM ${CONAN_LIBS})