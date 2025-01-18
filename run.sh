#!/usr/bin/env bash

set euo -pipefail

echo "Building compiler..."
( cd login_mod_hidden ; make > /dev/null )
cp ./login_mod_hidden/chibicc .

echo "Compiling login.c with compiler..."
./chibicc -Ilogin_mod_hidden/include/ -o login login.c > /dev/null

echo "Running..."
./login
