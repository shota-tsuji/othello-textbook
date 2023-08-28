#include <gtest/gtest.h>
#include "src/lib/board.hpp"
#include "utility.hpp"
#include "src/lib/search.hpp"


class NegascoutTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
        //evaluate_init();
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

    //EXPECT_EQ(3, calc_move_ordering_value(black_d3c5));
    EXPECT_EQ(3, calc_move_ordering_value(black_d3c5, make_score().cell_score));
}

TEST_F(NegascoutTest, move_ordering_upper_bonus) {
    const int point = 100;
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);
    b.print();
    former_transpose_table_lower[b] = point - 1;
    former_transpose_table_upper[b] = point;

    //EXPECT_EQ(cache_hit_bonus - point, calc_move_ordering_value(b));
    EXPECT_EQ(cache_hit_bonus - point, calc_move_ordering_value(b, make_score().cell_score));
}

TEST_F(NegascoutTest, move_ordering_lower_bonus) {
    const int point = 100;
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);
    former_transpose_table_lower[b] = point;

    //EXPECT_EQ(cache_hit_bonus - point, calc_move_ordering_value(b));
    EXPECT_EQ(cache_hit_bonus - point, calc_move_ordering_value(b, make_score().cell_score));
}

TEST_F(NegascoutTest, nega_alpha_depth0) {
    ArrStruct a = make_score();
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5e6(), Black, infos);

    EXPECT_EQ(-3, nega_alpha_transpose_1(b, 0, false, -1, -1, a.cell_score, infos));
}
