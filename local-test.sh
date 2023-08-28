# To exclude build/CMakeCache.txt, bind mount /app/build to empty volumes is used
# after bind mount local files to /app.
docker run -it --rm -v .:/app -v /app/build othello:latest sh -c \
  'cmake -S . -B build && \
  cmake --build build -v && \
  ./build/UnitTestExecutor && \
  lcov -d ./build/CMakeFiles/UnitTestExecutor.dir/ -c -o coverage.info && \
  lcov -r coverage.info */googletest/* test/* */c++/* -o coverage.info && \
  genhtml -o report/html --num-spaces 4 -s --legend coverage.info'