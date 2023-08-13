#include <gtest/gtest.h>
#include "board.hpp"

TEST(BoradTest, Initialization) {
    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};
    board b;
    int arr[64] = {0};
    b.translate_from_arr(arr, 0);

    bool same = true;
    for (int i = 0; i < n_board_idx; ++i) {
        if (b.board_idx[i] == expected[i]) {
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
    board b;
    int arr[64] = {0};

    board_init();
    b.translate_from_arr(arr, 0);

    EXPECT_TRUE(!b.legal(0));
}

// ...................0.......00.....111...........................
TEST(BoradTest, LegalJudge) {
    board b;
    int arr[64];
    for (int &i: arr) {
        i = 2;
    }
    arr[19] = 0;
    arr[27] = 0;
    arr[28] = 0;
    arr[34] = 1;
    arr[35] = 1;
    arr[36] = 1;
    board_init();
    b.translate_from_arr(arr, 0);
    b.print();

    EXPECT_TRUE(!b.legal(0));
    EXPECT_TRUE(b.legal(41));
}
