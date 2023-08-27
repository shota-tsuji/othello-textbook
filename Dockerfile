FROM ubuntu:latest
LABEL authors="shota-tsuji"
# https://github.com/srz-zumix/docker-googletest/tree/master

ARG BRANCH_OR_TAG=main
ARG CMAKE_OPTIONS=""

RUN apt-get update && apt-get upgrade -y \
  && apt-get install -q -y build-essential gcc g++ gdb clang cmake lcov \
    rsync ssh tar python3.11 git \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

# RUN git clone --depth=1 -b $BRANCH_OR_TAG -q https://github.com/google/googletest.git /googletest
# RUN mkdir -p /googletest/build
# WORKDIR /googletest/build
# RUN cmake .. ${CMAKE_OPTIONS} && make && make install

WORKDIR /app
# RUN rm -rf /googletest
COPY . .
# RUN ["g++", "-O0", "-g", "ai5_negascout.cpp", "-o", "ai.out"]
# cmake -S . -B build && cmake --build build -v && ctest --test-dir ./build --output-on-failure -V
# RUN ["cmake", "-S .", "-B build", "&&", "cmake", "--build build -v"]
# RUN ["cmake", "-S .", "-B build"]
RUN cmake -S . -B build && cmake --build build -v
RUN ./build/UnitTestExecutor \
    && lcov -d ./build/CMakeFiles/UnitTestExecutor.dir/ -c -o coverage.info \
    && lcov -r coverage.info */googletest/* test/* */c++/* -o coverage.info \
    && genhtml -o report/html --num-spaces 4 -s --legend coverage.info
# cd build/
# ./UnitTestExecutor
# cd CMakeFiles/UnitTestExecutor.dir/
# lcov -d . -c -o coverage.info
# lcov -r coverage.info */googletest/* test/* */c++/* -o coverageFiltered.info
# genhtml -o lcovHtml --num-spaces 4 -s --legend coverageFiltered.info
# /app/build/CMakeFiles/UnitTestExecutor.dir

# docker cp othello:/app/build/CMakeFiles/UnitTestExecutor.dir/lcovHtml /tmp/

