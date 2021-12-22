#!/bin/bash

set -euo pipefail

g++ -std=c++17 -fsanitize=address -fsanitize=leak -fsanitize=undefined \
    -Wall -Wextra -Werror -pedantic -pedantic-errors -march=native -mtune=native \
    -O2 $(find src/ -iname '*.cpp' -not -iname 'main.cpp' -type f) "$1" -pthread

if [ -f "$1.clargs" ]
then
    CLARGS="$(cat $1.clargs)"
else
    CLARGS=""
fi

if [ -f /usr/bin/time ]
then
    time ./a.out $CLARGS
else
    ./a.out $CLARGS
fi
