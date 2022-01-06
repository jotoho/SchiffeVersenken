#!/bin/sh
set -eu
clang-format -i $(find . -type f -iname '*.cpp' -printf '%p ' 2>/dev/null ) $(find . -type f -iname '*.hpp' -printf '%p ' 2>/dev/null )
