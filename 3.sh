#!/usr/bin/env bash

set euo -pipefail

echo "Building ouroboros compiler..."
( cd 3 ; make > /dev/null )
cp ./3/gcc .

echo "Compiling secretly backdoored compiler with obviously backdoored compiler..."
( cd unmodified/c_compiler ; make bad-gcc )
mv unmodified/c_compiler/bad-gcc .
