cmake_minimum_required(VERSION 3.25)
project(Othello_textbook CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(.)
include_directories(
        evaluation
        tests
)

add_executable(OthelloAI_Textbook
        # evaluation/board.hpp
        # evaluation/calc_additional_params.cpp
        # evaluation/mobility_surround_evaluation.hpp
        # ai1_forward1.cpp
        # ai2_negamax.cpp
        # ai3_negaalpha.cpp
        # ai4_negaalpha_fast.cpp
        ai5_negascout.cpp
        # ai6_pattern_evaluation.cpp
        # ai7_book.cpp
        # ai8_endgame_search.cpp
        board.hpp
        book.hpp
        cell_evaluation.hpp
        endgame_evaluation.hpp
        # pattern_mobility_surround_evaluation.hpp
        )

enable_testing()

add_executable(
        board_test
        tests/board_test.cc
)
target_link_libraries(
        board_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(board_test)