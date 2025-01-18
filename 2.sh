#!/usr/bin/env bash

set euo -pipefail

echo "Building modified compiler..."
( cd 2 ; make > /dev/null )
cp ./2/gcc .

echo "Compiling transparently modified login.c with modified compiler..."
./gcc -I./2/include/ -o login ./unmodified/login.c 

# echo "Running..."
#./login
