#include <gtest/gtest.h>
#include "board.hpp"

class TestBoard {
public:
    static std::vector<int> beginning() {
        std::vector<int> v(hw2, Vacant);
        v[D4] = White;
        v[E4] = Black;
        v[D5] = Black;
        v[E5] = White;

        return v;
    }
    static std::vector<int> d3c5() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
        v[E4] = Black;
        v[C5] = White;
        v[D5] = White;
        v[E5] = White;

        return v;
    }

    static std::vector<int> d3c5e6() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
        v[E4] = Black;
        v[C5] = White;
        v[D5] = White;
        v[E5] = Black;
        v[E6] = Black;

        return v;
    }

    static std::vector<int> all_black() {
        std::vector<int> v(hw2, Black);
        return v;
    }
};

TEST(Board, Initialization) {
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

TEST(Board, Initialization2) {
    board_init();

    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};

    board b;
    b.translate_from_arr(TestBoard::all_black(), Black);

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
TEST(Board, LegalJudgeAllBlack) {
    board_init();

    board b;
    b.translate_from_arr(TestBoard::all_black(), Black);

    EXPECT_FALSE(b.legal(A1));
}

// ...................0.......00.....111...........................
TEST(Board, LegalJudge) {
    board_init();

    board b;
    b.translate_from_arr(TestBoard::d3c5(), Black);
    b.print();

    EXPECT_FALSE(b.legal(A1));
    EXPECT_TRUE(b.legal(B6));
}

TEST(Board, EqualsToNextHandWhenMovedFromPreviousHand) {
    board_init();

    // d3c5e6
    board expected;
    expected.translate_from_arr(TestBoard::d3c5e6(), White);

    // d3c5
    board previous_board;
    previous_board.translate_from_arr(TestBoard::d3c5(), Black);
    board next = previous_board.move(E6);

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
    EXPECT_EQ(next.policy, E6);
}

// When calculating the hash value of the initial board, it is xxx.
TEST(Board, HashedValue) {
    board_init();

    board b;
    b.translate_from_arr(TestBoard::beginning(), Black);

    board::hash hashFunc;
    EXPECT_EQ(18446744073305302956, hashFunc(b));
}