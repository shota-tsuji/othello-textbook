FROM ubuntu:latest
LABEL authors="shota-tsuji"

RUN apt-get update \
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
  && apt-get clean

WORKDIR ./app
COPY . .
RUN ["g++", "-O0", "-g", "ai5_negascout.cpp", "-o", "ai.out"]
