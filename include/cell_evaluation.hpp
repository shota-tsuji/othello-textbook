#ifndef CELL_EVALUATION_H
#define CELL_EVALUATION_H
#pragma once

#include <iostream>
#include "const.hpp"
//#include "board.hpp"

#define hw 8            // ボードの大きさ
#define n_board_idx 38  // インデックスの個数 縦横各8x2、斜め11x2
using namespace std;

const int cell_weight[hw2] = {
        30, -12, 0, -1, -1, 0, -12, 30,
        -12, -15, -3, -3, -3, -3, -15, -12,
        0, -3, 0, -1, -1, 0, -3, 0,
        -1, -3, -1, -1, -1, -1, -3, -1,
        -1, -3, -1, -1, -1, -1, -3, -1,
        0, -3, 0, -1, -1, 0, -3, 0,
        -12, -15, -3, -3, -3, -3, -15, -12,
        30, -12, 0, -1, -1, 0, -12, 30
};

struct ArrStruct {
    int cell_score[hw / 2][n_line];
};

// 盤面のインデックス(行のインデックス)において黒番目線のスコアを前計算しておく
//inline ArrStruct make_score() {
ArrStruct make_score();

#endif //CELL_EVALUATION_H
