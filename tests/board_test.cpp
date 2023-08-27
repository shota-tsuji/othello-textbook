#include <gtest/gtest.h>
#include "board.hpp"
#include "utility.hpp"

class BoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
    }
};

TEST_F(BoardTest, Initialization) {
    Infos infos;
    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};
    int arr[64] = {0};
    board b;
    b.translate_from_arr_1(arr, 0, infos);

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

TEST_F(BoardTest, Initialization2) {
    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};

    board b;
    b.translate_from_arr(TestBoard::all_black(), Black, Infos());

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
TEST_F(BoardTest, LegalJudgeAllBlack) {
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::all_black(), Black, Infos());

    EXPECT_FALSE(b.is_legal(A1, infos));
}

// ...................0.......00.....111...........................
TEST_F(BoardTest, LegalJudge) {
    Infos infos;
    board b;
    b.translate_from_arr(TestBoard::d3c5(), Black, Infos());
    b.print();

    EXPECT_FALSE(b.is_legal(A1, infos));
    EXPECT_TRUE(b.is_legal(B6, infos));
}

TEST_F(BoardTest, EqualsToNextHandWhenMovedFromPreviousHand) {
    // d3c5e6
    board expected;
    expected.translate_from_arr(TestBoard::d3c5e6(), White, Infos());

    // d3c5
    board previous_board;
    previous_board.translate_from_arr(TestBoard::d3c5(), Black, Infos());
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

TEST_F(BoardTest, MoveFromBeginning) {
    board expected;
    expected.translate_from_arr(TestBoard::d3(), White, Infos());

    board b0;
    b0.translate_from_arr(TestBoard::beginning(), Black, Infos());
    board next = b0.move(D3);

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
    EXPECT_EQ(next.policy, D3);
}

TEST_F(BoardTest, HashedValue) {
    board::hash hashFunc;

    board b0;
    b0.translate_from_arr(TestBoard::beginning(), Black, Infos());

    EXPECT_EQ(18446744073305302956, hashFunc(b0));

    board b1;
    b1.translate_from_arr(TestBoard::d3c5(), Black, Infos());
    EXPECT_EQ(18446744073291327783, hashFunc(b1));

    board b2;
    b2.translate_from_arr(TestBoard::d3c5e6(), Black, Infos());
    EXPECT_EQ(18446744073212400438, hashFunc(b2));
}

TEST_F(BoardTest, Equality) {
    board b0;
    b0.translate_from_arr(TestBoard::beginning(), Black, Infos());
    board b1;
    b1.translate_from_arr(TestBoard::beginning(), White, Infos());
    board b2;
    b2.translate_from_arr(TestBoard::beginning(), Black, Infos());
    board b3;
    b3.translate_from_arr(TestBoard::all_black(), Black, Infos());

    EXPECT_EQ(b0, b0);
    EXPECT_EQ(b0, b2);
    EXPECT_NE(b0, b1);
    EXPECT_NE(b0, b3);
}