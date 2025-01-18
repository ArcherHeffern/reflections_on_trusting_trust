#!/usr/bin/env bash

set euo -pipefail

echo "Compiling compiler with ouroboros compiler..."
( cd unmodified/c_compiler ; make bad-gcc )
mv unmodified/c_compiler/bad-gcc ./bad-gcc-2

echo "Compiling login.c with ouroboros compiler..."
echo "TODO"