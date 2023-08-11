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