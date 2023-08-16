#include <gtest/gtest.h>
#include "board.hpp"

TEST(BoradTest, Initialization) {
    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};
    board_init();
    int arr[64] = {0};
    board b;
    b.translate_from_arr(arr, 0);

    bool same = true;
    for (int i = 0; i < n_board_idx; ++i) {
        if (b.board_idx[i] != expected[i]) {
            same = false;
            break;
        }
    }
    EXPECT_TRUE(same);
    EXPECT_EQ(b.player, 0);
    EXPECT_EQ(b.n_stones, 64);
}

// 0000000000000000000000000000000000000000000000000000000000000000
TEST(BoradTest, LegalJudgeAllBlack) {
    std::vector<int> board_array(hw2, 0);

    board_init();
    board b;
    b.translate_from_arr(board_array, 0);

    EXPECT_TRUE(!b.legal(0));
}

std::vector<int> make_vector_d3c5() {
    std::vector<int> v(hw2, 2);
    v[19] = 0;
    v[27] = 0;
    v[28] = 0;
    v[34] = 1;
    v[35] = 1;
    v[36] = 1;

    return v;
}

// ...................0.......00.....111...........................
TEST(BoradTest, LegalJudge) {
    board_init();

    board b;
    b.translate_from_arr(make_vector_d3c5(), Black);
    b.print();

    EXPECT_TRUE(!b.legal(0));
    EXPECT_TRUE(b.legal(41));
}

std::vector<int> make_vector_d3c5e6() {
    std::vector<int> v(hw2, 2);
    v[19] = 0;
    v[27] = 0;
    v[28] = 0;
    v[34] = 1;
    v[35] = 1;
    v[36] = 0;
    v[44] = 0;

    return v;
}

TEST(BoradTest, EqualsToNextHandWhenMovedFromPreviousHand) {
    board_init();

    // d3c5e6
    board expected;
    expected.translate_from_arr(make_vector_d3c5e6(), white);

    // d3c5
    board previous_board;
    previous_board.translate_from_arr(make_vector_d3c5(), Black);
    board next = previous_board.move(44);

    bool same = true;
    for (int i = 0; i < n_board_idx; ++i) {
        if (next.board_idx[i] != expected.board_idx[i]) {
            same = false;
            break;
        }
    }
    EXPECT_TRUE(same);
    EXPECT_EQ(next.player, expected.player);
    EXPECT_EQ(next.n_stones, expected.n_stones);
    EXPECT_EQ(next.policy, 44);
}
