FROM debian:bookworm

# Install necessary tools
RUN apt-get update && apt-get install -y \
  cmake \
  ninja-build \
  git \
  build-essential \
  pkg-config \
  zip \
  xz-utils \
  wget \
  python3 \
  python3-pip \
  mingw-w64 \
  && apt-get clean

# Default workdir
WORKDIR /app

# CMake configure + build script (optional override)
COPY ./cmake/mingw-toolchain.cmake /toolchain.cmake
