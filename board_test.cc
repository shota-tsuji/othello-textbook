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
    static std::vector<int> d3() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
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

class BoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
    }
};

TEST_F(BoardTest, Initialization) {
    int expected[n_board_idx] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80,
                                 242, 242, 80, 26, 8, 2, 0, 2, 8, 26, 80, 242};
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

TEST_F(BoardTest, Initialization2) {
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
TEST_F(BoardTest, LegalJudgeAllBlack) {
    board b;
    b.translate_from_arr(TestBoard::all_black(), Black);

    EXPECT_FALSE(b.legal(A1));
}

// ...................0.......00.....111...........................
TEST_F(BoardTest, LegalJudge) {
    board b;
    b.translate_from_arr(TestBoard::d3c5(), Black);
    b.print();

    EXPECT_FALSE(b.legal(A1));
    EXPECT_TRUE(b.legal(B6));
}

TEST_F(BoardTest, EqualsToNextHandWhenMovedFromPreviousHand) {
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

TEST_F(BoardTest, MoveFromBeginning) {
    board expected;
    expected.translate_from_arr(TestBoard::d3(), White);

    board b0;
    b0.translate_from_arr(TestBoard::beginning(), Black);
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
    b0.translate_from_arr(TestBoard::beginning(), Black);

    EXPECT_EQ(18446744073305302956, hashFunc(b0));

    board b1;
    b1.translate_from_arr(TestBoard::d3c5(), Black);
    EXPECT_EQ(18446744073291327783, hashFunc(b1));

    board b2;
    b2.translate_from_arr(TestBoard::d3c5e6(), Black);
    EXPECT_EQ(18446744073212400438, hashFunc(b2));
}

TEST_F(BoardTest, Equality) {
    board b0;
    b0.translate_from_arr(TestBoard::beginning(), Black);
    board b1;
    b1.translate_from_arr(TestBoard::beginning(), White);
    board b2;
    b2.translate_from_arr(TestBoard::beginning(), Black);
    board b3;
    b3.translate_from_arr(TestBoard::all_black(), Black);

    EXPECT_EQ(b0, b0);
    EXPECT_EQ(b0, b2);
    EXPECT_NE(b0, b1);
    EXPECT_NE(b0, b3);
}