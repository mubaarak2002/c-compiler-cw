#!/bin/bash

make clean
make
cd bin
./c_compiler -S ../src/in.code.c -o ../src/out.code.s
cd ..
