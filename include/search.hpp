#ifndef OTHELLO_TEXTBOOK_SEARCH_HPP
#define OTHELLO_TEXTBOOK_SEARCH_HPP

#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
#include "const.hpp"
#include "board.hpp"
#include "cell_evaluation.hpp"
#include "board.hpp"

const int INF = 100000000;   // 大きな値
const int CACHE_HIT_BONUS = 1000;   // 前回の探索で枝刈りされなかったノードへのボーナス
unsigned long long visited_nodes; // 訪問ノード数

using namespace std;
unordered_map<board, int, board::hash> transpose_table_upper;          // 現在の探索結果を入れる置換表(上限): 同じ局面に当たった時用
unordered_map<board, int, board::hash> transpose_table_lower;          // 現在の探索結果を入れる置換表(下限): 同じ局面に当たった時用
unordered_map<board, int, board::hash> former_transpose_table_upper;   // 前回の探索結果が入る置換表(上限): move orderingに使う
unordered_map<board, int, board::hash> former_transpose_table_lower;   // 前回の探索結果が入る置換表(下限): move orderingに使う

// move ordering用評価値の計算
inline int calc_move_ordering_value(const board b, int cell_score[hw / 2][n_line]) {
    int res;
    if (former_transpose_table_upper.find(b) != former_transpose_table_upper.end()) {
        // 前回の探索で上限値が格納されていた場合
        res = CACHE_HIT_BONUS - former_transpose_table_upper[b];
    } else if (former_transpose_table_lower.find(b) != former_transpose_table_lower.end()) {
        // 前回の探索で下限値が格納されていた場合
        res = CACHE_HIT_BONUS - former_transpose_table_lower[b];
    } else {
        // 前回の探索で枝刈りされた
        res = -evaluate(b, cell_score);
    }
    return res;
}
inline int calc_move_ordering_value_new(const board b, Infos infos) {
    int res;
    if (former_transpose_table_upper.find(b) != former_transpose_table_upper.end()) {
        // 前回の探索で上限値が格納されていた場合
        res = CACHE_HIT_BONUS - former_transpose_table_upper[b];
    } else if (former_transpose_table_lower.find(b) != former_transpose_table_lower.end()) {
        // 前回の探索で下限値が格納されていた場合
        res = CACHE_HIT_BONUS - former_transpose_table_lower[b];
    } else {
        // 前回の探索で枝刈りされた
        res = -evaluate_new(b, infos);
    }
    return res;
}

// move orderingと置換表つきnegaalpha法 null windows searchに使う
int nega_alpha_transpose_1(board b, int depth, bool passed, int alpha, int beta, Infos infos) {
    ++visited_nodes;

    // 葉ノードでは評価関数を実行する
    if (depth == 0)
        return evaluate(b, infos.csi.cell_score);

    // 置換表から上限値と下限値があれば取得
    int u = INF, l = -INF;
    if (transpose_table_upper.find(b) != transpose_table_upper.end())
        u = transpose_table_upper[b];
    if (transpose_table_lower.find(b) != transpose_table_lower.end())
        l = transpose_table_lower[b];

    // u==l、つまりもうminimax値が求まっていれば探索終了
    if (u == l)
        return u;

    // 置換表の値を使って探索窓を狭められる場合は狭める
    alpha = max(alpha, l);
    beta = min(beta, u);

    // 葉ノードでなければ子ノードを列挙
    int coord, g, max_score = -INF, canput = 0;
    vector<board> child_nodes;
    for (coord = 0; coord < hw2; ++coord) {
        if (b.is_legal(coord, infos)) {
            child_nodes.push_back(b.move(coord, infos));
            child_nodes[canput].value = calc_move_ordering_value(child_nodes[canput], infos.csi.cell_score);
            ++canput;
        }
    }

    // パスの処理 手番を交代して同じ深さで再帰する
    if (canput == 0) {
        // 2回連続パスなら評価関数を実行
        if (passed)
            return evaluate(b, infos.csi.cell_score);
        b.player = 1 - b.player;
        return -nega_alpha_transpose_1(b, depth, true, -beta, -alpha, infos);
    }

    // move ordering実行
    if (canput >= 2)
        sort(child_nodes.begin(), child_nodes.end());

    // 探索
    for (const board& nb: child_nodes) {
        g = -nega_alpha_transpose_1(nb, depth - 1, false, -beta, -alpha, infos);
        if (g >= beta) { // 興味の範囲よりもminimax値が上のときは枝刈り fail high
            if (g > l) {
                // 置換表の下限値に登録
                transpose_table_lower[b] = g;
            }
            return g;
        }
        alpha = max(alpha, g);
        max_score = max(max_score, g);
    }

    if (max_score < alpha) {
        // 置換表の下限値に登録 fail low
        transpose_table_upper[b] = max_score;
    } else {
        // minimax値が求まった
        transpose_table_upper[b] = max_score;
        transpose_table_lower[b] = max_score;
    }
    return max_score;
}
#endif //OTHELLO_TEXTBOOK_SEARCH_HPP
