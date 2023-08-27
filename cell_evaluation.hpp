#ifndef CELL_EVALUATION_H
#define CELL_EVALUATION_H
#pragma once

#include <iostream>
#include "board.hpp"

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
inline ArrStruct make_score() {
    ArrStruct a;
    int idx, i, place, b, w;

    for (idx = 0; idx < n_line; ++idx) {
        b = create_one_color(idx, 0);
        w = create_one_color(idx, 1);
        for (i = 0; i < hw / 2; ++i)
            a.cell_score[i][idx] = 0;
        for (place = 0; place < hw; ++place) {
            for (i = 0; i < hw / 2; ++i) {
                a.cell_score[i][idx] += (1 & (b >> place)) * cell_weight[i * hw + place];
                a.cell_score[i][idx] -= (1 & (w >> place)) * cell_weight[i * hw + place];
            }
        }
    }

    return a;
}

inline int evaluate(board b, int cell_score[hw / 2][n_line]) {
    int res = 0, i;
    for (i = 0; i < hw / 2; ++i)
        res += cell_score[i][b.board_idx[i]];
    for (i = 0; i < hw / 2; ++i)
        // 折り返して配列確認している?
        res += cell_score[hw / 2 - 1 - i][b.board_idx[hw / 2 + i]];
    if (b.player == White)
        res = -res;
    return res;
}

#endif //CELL_EVALUATION_H
