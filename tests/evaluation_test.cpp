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
