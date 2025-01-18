#!/usr/bin/env bash

set euo -pipefail

echo "Compiling login.c with ouroboros compiler..."
( cd unmodified ; ../bad-gcc -I./c_compiler/include/ -o login ./login.c )
mv unmodified/login ./bad-login

echo "Compiling ouroboros compiler with ouroboros compiler..."
( cd unmodified/c_compiler ; make -B bad-gcc )
mv unmodified/c_compiler/bad-gcc ./bad-gcc