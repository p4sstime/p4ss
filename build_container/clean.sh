#!/bin/bash
set -euo pipefail

script=$(readlink -f -- "$0")
pushd "$(dirname -- "$script")" > /dev/null
pwd="$(pwd)"
THIS_DIR="${THIS_DIR:-$pwd}"

# Run this script in the Sniper container

# Let's say we run as /home/lucy/p4ss/build/myscript
# This mounts /home/lucy/p4ss, and then launches
# build/myscript inside of that.

source ../src/sdk_container
run_in_sniper "$@"

cmake --build . --target clean $@