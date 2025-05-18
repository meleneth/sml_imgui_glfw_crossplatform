#!/bin/bash

set -exuo pipefail

cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
