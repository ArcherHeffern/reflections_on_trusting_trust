#!/usr/bin/env bash

set euo -pipefail

read -p "Use gcc(1) or custom compiler(2)? " COMPILER 
case $COMPILER in
    1)
        echo "Building compiler using gcc"
        ( cd compiler_patched ; make -B )
        cp ./compiler_patched/compiler compiler
    ;;
    2)
        echo "Building compiler using compiler"
        ( cd compiler_patched ; make bad-compiler -B )
        cp ./compiler_patched/bad-compiler compiler
    ;;
    *)
    echo "No such option, exiting..."
    exit 1
esac