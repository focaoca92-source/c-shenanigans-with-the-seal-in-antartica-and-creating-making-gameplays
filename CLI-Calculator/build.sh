#!/bin/bash

mkdir -p build
clang++-19 -g -O0 -std=c++23 -stdlib=libc++ -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fmodule-file=std=std.pcm CLI-Calculator/main.cpp CLI-Calculator/calculator.cpp std.pcm -o build/calculator
