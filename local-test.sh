# To exclude build/CMakeCache.txt, bind mount /app/build to empty volumes is used
# after bind mount local files to /app.
docker run -it --rm -v .:/app -v /app/build othello:latest sh -c \
  'cmake -S . -B build && \
  cmake --build build -v && \
  ./build/unit-tests && \
  lcov -d ./build/CMakeFiles/unit-tests.dir/ -c -o coverage.info && \
  lcov -r coverage.info */googletest/* test/* */c++/* -o coverage.info && \
  genhtml -o report/html --num-spaces 4 -s --legend coverage.info'