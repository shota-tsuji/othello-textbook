#include <gtest/gtest.h>
#include "include/board.hpp"
#include "include/cell_evaluation.hpp"
#include "utility.hpp"
#include "include/const.hpp"

class EvaluationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code that runs before each test case
        board_init();
        //evaluate_init();
    }
};

TEST_F(EvaluationTest, d3c5) {
    ArrStruct a = make_score();
    board black_d3c5;
    black_d3c5.translate_from_arr(TestBoard::d3c5(), Black, Infos());
    black_d3c5.print();

    board white_d3c5;
    white_d3c5.translate_from_arr(TestBoard::d3c5(), White, Infos());
    white_d3c5.print();

    EXPECT_EQ(0, evaluate(black_d3c5, a.cell_score));
    EXPECT_EQ(0, evaluate(white_d3c5, a.cell_score));
}

TEST_F(EvaluationTest, d3c5e6) {
    ArrStruct a = make_score();
    board black_d3c5e6;
    black_d3c5e6.translate_from_arr(TestBoard::d3c5e6(), Black, Infos());
    black_d3c5e6.print();


    board white_d3c5e6;
    white_d3c5e6.translate_from_arr(TestBoard::d3c5e6(), White, Infos());
    white_d3c5e6.print();

    EXPECT_EQ(-3, evaluate(black_d3c5e6, a.cell_score));
    EXPECT_EQ(3, evaluate(white_d3c5e6, a.cell_score));
}

TEST_F(EvaluationTest, all_black) {
    ArrStruct a = make_score();
    board black_all_black;
    black_all_black.translate_from_arr(TestBoard::all_black(), Black, Infos());
    black_all_black.print();

    board white_all_black;
    white_all_black.translate_from_arr(TestBoard::all_black(), White, Infos());
    white_all_black.print();

    EXPECT_EQ(-104, evaluate(black_all_black, a.cell_score));
    EXPECT_EQ(104, evaluate(white_all_black, a.cell_score));
}
