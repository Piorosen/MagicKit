#!/bin/bash

rm -rf test.asm
rm -rf test
rm -rf main.h
rm -rf MagicKit

clang++ -O3 -fPIC -shared -o test test.cpp
objdump -d ./test > test.asm
python3 test.py > main.h

g++ -O3 -o MagicKit main.cpp && ./MagicKit

# rm -rf main.h
rm -rf MagicKit
rm -rf test.asm
rm -rf test
