#!/bin/bash


rm -rf test.asm
rm -rf test
rm -rf main.h
rm -rf MagicKit

clang++ -O0 -fPIC -shared -o test test.cpp
objdump -d ./test > test.asm
python3 test.py > main.h

# rm -rf test.asm
# rm -rf test

g++ -O0 -o MagicKit main.cpp
./MagicKit

