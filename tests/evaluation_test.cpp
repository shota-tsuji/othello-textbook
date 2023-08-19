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
    board b;
    b.translate_from_arr(TestBoard::d3c5(), Black);
    b.print();

    EXPECT_EQ(0, evaluate(b));
}

TEST_F(EvaluationTest, d3c5e6) {
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black);
    b.print();

    EXPECT_EQ(-3, evaluate(b));
}

TEST_F(EvaluationTest, all_black) {
    board b;
    b.translate_from_arr(TestBoard::all_black(), Black);
    b.print();

    EXPECT_EQ(-104, evaluate(b));
}
