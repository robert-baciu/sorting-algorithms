#!/bin/bash
mkdir -p bin
cd src/
g++ -O0 *.cpp -o ../bin/benchmark-O0 && echo "Compiled benchmark-O0"
g++ -O1 *.cpp -o ../bin/benchmark-O1 && echo "Compiled benchmark-O1"
g++ -O2 *.cpp -o ../bin/benchmark-O2 && echo "Compiled benchmark-O2"
g++ -O3 *.cpp -o ../bin/benchmark-O3 && echo "Compiled benchmark-O3"
