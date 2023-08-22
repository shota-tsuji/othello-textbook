FROM ubuntu:latest
LABEL authors="shota-tsuji"

RUN apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y ssh \
    build-essential \
    gcc \
    g++ \
    gdb \
    clang \
    cmake \
    rsync \
    tar \
    python3.11 \
    git \
  && apt-get clean

WORKDIR ./app
COPY . .
# RUN ["g++", "-O0", "-g", "ai5_negascout.cpp", "-o", "ai.out"]
# cmake -S . -B build && cmake --build build -v && ctest --test-dir ./build --output-on-failure -V
# RUN ["cmake", "-S .", "-B build", "&&", "cmake", "--build build -v"]
# RUN ["cmake", "-S .", "-B build"]
RUN cmake -S . -B build && cmake --build build -v
