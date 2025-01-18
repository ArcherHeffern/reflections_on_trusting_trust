#!/usr/bin/env bash

set euo -pipefail

echo "Building ouroboros compiler..."
( cd 3 ; make -B )
cp ./3/gcc bad-gcc