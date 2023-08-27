FROM ubuntu:latest
LABEL authors="shota-tsuji"
# https://github.com/srz-zumix/docker-googletest/tree/master

ARG BRANCH_OR_TAG=main
ARG CMAKE_OPTIONS=""

RUN apt-get update && apt-get upgrade -y \
  && apt-get install -q -y build-essential gcc g++ gdb clang cmake lcov \
    rsync ssh tar python3.11 git \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN cmake -S . -B build && cmake --build build -v
RUN ./build/UnitTestExecutor \
    && lcov -d ./build/CMakeFiles/UnitTestExecutor.dir/ -c -o coverage.info \
    && lcov -r coverage.info */googletest/* test/* */c++/* -o coverage.info \
    && genhtml -o report/html --num-spaces 4 -s --legend coverage.info

# cmake -S . -B build && cmake --build build -v && ctest --test-dir ./build --output-on-failure -V
# docker cp othello:/app/build/CMakeFiles/UnitTestExecutor.dir/lcovHtml /tmp/

