#include <gtest/gtest.h>
#include "board.hpp"
#include "cell_evaluation.hpp"
#include "utility.hpp"

class EvaluationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
        evaluate_init();
    }
};

TEST_F(EvaluationTest, d3c5) {
    board black_d3c5;
    black_d3c5.translate_from_arr(TestBoard::d3c5(), Black);
    black_d3c5.print();

    board white_d3c5;
    white_d3c5.translate_from_arr(TestBoard::d3c5(), White);
    white_d3c5.print();

    EXPECT_EQ(0, evaluate(black_d3c5));
    EXPECT_EQ(0, evaluate(white_d3c5));
}

TEST_F(EvaluationTest, d3c5e6) {
    board black_d3c5e6;
    black_d3c5e6.translate_from_arr(TestBoard::d3c5e6(), Black);
    black_d3c5e6.print();


    board white_d3c5e6;
    white_d3c5e6.translate_from_arr(TestBoard::d3c5e6(), White);
    white_d3c5e6.print();

    EXPECT_EQ(-3, evaluate(black_d3c5e6));
    EXPECT_EQ(3, evaluate(white_d3c5e6));
}

TEST_F(EvaluationTest, all_black) {
    board black_all_black;
    black_all_black.translate_from_arr(TestBoard::all_black(), Black);
    black_all_black.print();

    board white_all_black;
    white_all_black.translate_from_arr(TestBoard::all_black(), White);
    white_all_black.print();

    EXPECT_EQ(-104, evaluate(black_all_black));
    EXPECT_EQ(104, evaluate(white_all_black));
}
