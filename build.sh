#!/usr/bin/env bash

# cleaning
rm -rf bin
rm -rf int
mkdir bin
mkdir int

# compiling
gcc src/entry.c -Isrc/** -c -o int/entry
gcc src/orchestra.c -Isrc/** -c -o int/orchestra
gcc src/sys_call.c -Isrc/** -c -o int/sys_call
gcc src/stack.c -Isrc/** -c -o int/stack

# linking
gcc int/entry int/orchestra int/sys_call int/stack -o bin/xen
