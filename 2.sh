#!/usr/bin/env bash

set euo -pipefail

echo "Building compiler..."
( cd 2 ; make > /dev/null )
cp ./2/chibicc .

echo "Compiling login.c with compiler..."
./chibicc -I2/include/ -o login login.c 

# echo "Running..."
#./login
