#!/usr/bin/env bash

set euo -pipefail

echo "Building unmodified compiler..."
( cd unmodified/c_compiler && make gcc )
cp ./unmodified/c_compiler/gcc .

echo "Compiling unmodified login.c with unmodified compiler..."
./gcc -I./unmodified/c_compiler/include/ -o login ./unmodified/login.c 

