#!/bin/bash
### Wrapper to run both configure and build.
set -euo pipefail
script=$(readlink -f -- "$0")
pushd "$(dirname -- "$script")" > /dev/null
pwd="$(pwd)"
THIS_DIR="${THIS_DIR:-$pwd}"

./configure.sh $@
./build.sh