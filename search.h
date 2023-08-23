#ifndef OTHELLO_TEXTBOOK_SEARCH_H
#define OTHELLO_TEXTBOOK_SEARCH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "board.hpp"
#include "cell_evaluation.hpp"

#define inf 100000000               // 大きな値
#define cache_hit_bonus 1000        // 前回の探索で枝刈りされなかったノードへのボーナス

using namespace std;
unordered_map<board, int, board::hash> transpose_table_upper;          // 現在の探索結果を入れる置換表(上限): 同じ局面に当たった時用
unordered_map<board, int, board::hash> transpose_table_lower;          // 現在の探索結果を入れる置換表(下限): 同じ局面に当たった時用
unordered_map<board, int, board::hash> former_transpose_table_upper;   // 前回の探索結果が入る置換表(上限): move orderingに使う
unordered_map<board, int, board::hash> former_transpose_table_lower;   // 前回の探索結果が入る置換表(下限): move orderingに使う

// move ordering用評価値の計算
inline int calc_move_ordering_value(const board b) {
    int res;
    if (former_transpose_table_upper.find(b) != former_transpose_table_upper.end()) {
        // 前回の探索で上限値が格納されていた場合
        res = cache_hit_bonus - former_transpose_table_upper[b];
    } else if (former_transpose_table_lower.find(b) != former_transpose_table_lower.end()) {
        // 前回の探索で下限値が格納されていた場合
        res = cache_hit_bonus - former_transpose_table_lower[b];
    } else {
        // 前回の探索で枝刈りされた
        res = -evaluate(b);
    }
    return res;
}

#endif //OTHELLO_TEXTBOOK_SEARCH_H
