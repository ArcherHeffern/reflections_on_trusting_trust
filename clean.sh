#!/usr/bin/env bash

set euo -pipefail

( cd 1 ; rm -f login )
( cd 2 ; make clean )
( cd 3 ; make clean )
( cd unmodified/c_compiler ; make clean )
rm -f login bad-login gcc 
