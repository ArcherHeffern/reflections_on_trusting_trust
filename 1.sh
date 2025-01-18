#!/usr/bin/env bash

set euo -pipefail

echo "Building unmodified compiler..."
( cd unmodified/c_compiler ; make > /dev/null )
cp ./unmodified/c_compiler/gcc .

echo "Compiling login.c with compiler..."
./gcc -I./unmodified/c_compiler/include/ -o login 1/login.c 

