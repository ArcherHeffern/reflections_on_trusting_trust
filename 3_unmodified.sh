#!/usr/bin/env bash

set euo -pipefail

echo "Building compiler..."
( cd 3/unmodified ; make > /dev/null )
cp ./3/unmodified/chibicc .

echo "Compiling login.c with compiler..."
./chibicc -I3/unmodified/include/ -o login login.c 

# echo "Running..."
#./login
