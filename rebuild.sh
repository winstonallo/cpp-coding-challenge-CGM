#!/bin/sh

rm -rf ./build
conan install . --build=gtest/1.15.0
cd ./build
cmake .. -DCMAKE_BUILD_TYPE=release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make