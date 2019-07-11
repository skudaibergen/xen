#!/usr/bin/env bash

# compiling
gcc src/main.c -c -o int/main
gcc src/argv_parser.c -c -o int/argv_parser

# linking
gcc int/main int/argv_parser -o bin/xen
