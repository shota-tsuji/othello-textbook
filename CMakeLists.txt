cmake_minimum_required(VERSION 3.22)
# cmake_minimum_required(VERSION 3.25)
project(Othello_textbook CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_EXE_LINKER_FLAGS "--coverage")
# set(CMAKE_CXX_COMPILER /usr/bin/g++)
# set(CMAKE_CXX_FLAGS "--coverage -fprofile-instr-generate -fcoverage-mapping")
file(GLOB MY_TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
file(GLOB OTHELLO_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
set(MY_TEST_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(MY_BINARY_NAME "unit-tests")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        03597a01ee50ed33e9dfd640b249b4be3799d395 # release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(.)
include_directories(
        evaluation
        tests
)

add_executable(othello
        # evaluation/board.hpp
        # evaluation/calc_additional_params.cpp
        # evaluation/mobility_surround_evaluation.hpp
        # ai1_forward1.cpp
        # ai2_negamax.cpp
        # ai3_negaalpha.cpp
        # ai4_negaalpha_fast.cpp
        src/bin/ai5_negascout.cpp
        # ai6_pattern_evaluation.cpp
        # ai7_book.cpp
        # ai8_endgame_search.cpp
        include/board.hpp
        book.hpp
        include/cell_evaluation.hpp
        endgame_evaluation.hpp
        include/board.cpp
        include/cell_evaluation.cpp
        # pattern_mobility_surround_evaluation.hpp
        )

enable_testing()

add_executable(${MY_BINARY_NAME} ${MY_TEST_SRCS} ${OTHELLO_LIBRARY})
target_link_libraries(${MY_BINARY_NAME} GTest::gtest_main)

#add_executable(board_test tests/board_test.cc)
#target_link_libraries(board_test GTest::gtest_main)
#
#add_executable(evaluation_test tests/evaluation_test.cpp)
#target_link_libraries(evaluation_test GTest::gtest_main)
#
#add_executable(negascout_test tests/negascout_test.cpp)
#target_link_libraries(negascout_test GTest::gtest_main)

include(GoogleTest)
# gtest_discover_tests(board_test)
# gtest_discover_tests(evaluation_test)
# gtest_discover_tests(negascout_test)

# ctest_coverage(build board_test)
# ctest_coverage(evaluation_test)
# ctest_coverage(negascout_test)

# /Library/Developer/CommandLineTools/usr/bin/llvm-profdata merge -sparse default.profraw -o build/coverage.profdata
# /Library/Developer/CommandLineTools/usr/bin/llvm-cov show build/board_test -instr-profile=build/coverage.profdata -format=html -o coverage_html