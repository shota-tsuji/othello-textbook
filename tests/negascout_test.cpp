#include <gtest/gtest.h>
#include "board.hpp"
#include "utility.hpp"
#include "search.h"


class NegascoutTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
        evaluate_init();
    }
};

// TEST_F(NegascoutTest, d3c5) {
//     board black_d3c5;
//     black_d3c5.translate_from_arr(TestBoard::d3c5(), Black);
//     black_d3c5.print();
//
//     EXPECT_EQ(0, search(black_d3c5, 8));
// }

TEST_F(NegascoutTest, move_ordering) {
    board black_d3c5;
    black_d3c5.translate_from_arr(TestBoard::d3c5e6(), Black);
    black_d3c5.print();

    EXPECT_EQ(3, calc_move_ordering_value(black_d3c5));
}
