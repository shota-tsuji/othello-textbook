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

TEST(BoradTest, Initialization2) {
    board_init();

    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};

    board b;
    std::vector<int> board_array(hw2, Black);
    b.translate_from_arr(board_array, Black);

    bool same = true;
    for (int i = 0; i < n_board_idx; ++i) {
        if (b.board_idx[i] != expected[i]) {
            same = false;
            break;
        }
    }
    EXPECT_TRUE(same);
    EXPECT_EQ(b.player, Black);
    EXPECT_EQ(b.n_stones, hw2);
}

// 0000000000000000000000000000000000000000000000000000000000000000
TEST(BoradTest, LegalJudgeAllBlack) {
    board_init();

    board b;
    std::vector<int> board_array(hw2, Black);
    b.translate_from_arr(board_array, Black);

    EXPECT_FALSE(b.legal(0));
}

class TestBoard {
public:
    static std::vector<int> d3c5() {
        std::vector<int> v(hw2, Vacant);
        v[19] = Black;
        v[27] = Black;
        v[28] = Black;
        v[34] = White;
        v[35] = White;
        v[36] = White;

        return v;
    }
};

// ...................0.......00.....111...........................
TEST(BoradTest, LegalJudge) {
    board_init();

    board b;
    b.translate_from_arr(TestBoard::d3c5(), Black);
    b.print();

    EXPECT_FALSE(b.legal(0));
    EXPECT_TRUE(b.legal(41));
}

std::vector<int> make_vector_d3c5e6() {
    std::vector<int> v(hw2, Vacant);
    v[19] = Black;
    v[27] = Black;
    v[28] = Black;
    v[34] = White;
    v[35] = White;
    v[36] = Black;
    v[44] = Black;

    return v;
}

TEST(BoradTest, EqualsToNextHandWhenMovedFromPreviousHand) {
    board_init();

    // d3c5e6
    board expected;
    expected.translate_from_arr(make_vector_d3c5e6(), White);

    // d3c5
    board previous_board;
    previous_board.translate_from_arr(TestBoard::d3c5(), Black);
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
