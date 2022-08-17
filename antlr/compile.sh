#!/bin/bash
cd "$(dirname "$0")"
rm -r antlr4cpp
unzip antlr4-cpp-runtime-4.10.1-source.zip -d antlr4cpp
cd antlr4cpp
cmake -DCMAKE_BUILD_TYPE=Debug .
make
cd ..
cd binary/build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
