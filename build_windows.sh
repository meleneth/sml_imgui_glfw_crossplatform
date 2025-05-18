#!/bin/bash
set -euo pipefail

PROJECT_NAME="sml_imgui"
BUILD_DIR="build-win"

# Ensure output directory exists on host
mkdir -p "$BUILD_DIR"

docker build -t winbuilder .

docker run --rm \
  -v "$PWD":/app \
  -w /app \
  winbuilder \
  bash -c "\
    cmake -B $BUILD_DIR -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=/toolchain.cmake \
      -DCMAKE_BUILD_TYPE=Release && \
    cmake --build $BUILD_DIR"

echo ""
echo "✅ Windows build complete: $BUILD_DIR/${PROJECT_NAME}.exe"
