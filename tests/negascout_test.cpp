#include <gtest/gtest.h>
#include "include/board.hpp"
#include "utility.hpp"
#include "include/search.hpp"
#include "include/const.hpp"


class NegascoutTest : public ::testing::Test {
protected:
    void SetUp() override {
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
    Infos infos;
    board black_d3c5;
    black_d3c5.translate_from_arr(TestBoard::d3c5e6(), Black, infos);
    black_d3c5.print();

    EXPECT_EQ(3, calc_move_ordering_value_new(black_d3c5, infos));
}

TEST_F(NegascoutTest, move_ordering_upper_bonus) {
    const int point = 100;
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);
    b.print();
    former_transpose_table_lower[b] = point - 1;
    former_transpose_table_upper[b] = point;

    EXPECT_EQ(CACHE_HIT_BONUS - point, calc_move_ordering_value_new(b, infos));
}

TEST_F(NegascoutTest, move_ordering_lower_bonus) {
    const int point = 100;
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);
    former_transpose_table_lower[b] = point;

    EXPECT_EQ(CACHE_HIT_BONUS - point, calc_move_ordering_value_new(b, infos));
}

TEST_F(NegascoutTest, nega_alpha_depth0) {
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);

    EXPECT_EQ(-3, nega_alpha_transpose_1(b, 0, false, -1, -1, infos));
}
