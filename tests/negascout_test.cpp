#include <gtest/gtest.h>
//#include "board.hpp"
#include "utility.hpp"
#include "ai5_negascout.cpp"


class NegascoutTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
        evaluate_init();
    }
};

TEST_F(NegascoutTest, d3c5) {
    board black_d3c5;
    black_d3c5.translate_from_arr(TestBoard::d3c5(), Black);
    black_d3c5.print();

    EXPECT_EQ(0, search(black_d3c5, 8));
}
