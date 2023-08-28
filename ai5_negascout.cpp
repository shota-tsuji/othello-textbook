#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "src/lib/board.hpp"
#include "src/lib/cell_evaluation.hpp"
#include "search.h"

using namespace std;

#define inf 100000000               // 大きな値
#define cache_hit_bonus 1000        // 前回の探索で枝刈りされなかったノードへのボーナス

// 初期化
//inline void init() {
//    board_init();
//    evaluate_init();
//}

// 標準入力からボードの状態を配列に受け取る
inline void input_board(int arr[]) {
    char elem;
    for (int i = 0; i < hw2; ++i) {
        cin >> elem;
        if (elem == '0')
            arr[i] = Black;
        else if (elem == '1')
            arr[i] = White;
        else
            arr[i] = Vacant;
    }
}


// negascout法
int nega_scout_1(board b, int depth, bool passed, int alpha, int beta, int cell_score[hw / 2][n_line], Infos infos) {
    ++visited_nodes;

    // 葉ノードでは評価関数を実行する
    if (depth == 0)
        return evaluate(b, cell_score);

    // 置換表から上限値と下限値があれば取得
    int u = inf, l = -inf;
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
    int coord, g, max_score = -inf, canput = 0;
    vector<board> child_nodes;
    for (coord = 0; coord < hw2; ++coord) {
        if (b.is_legal(coord, infos)) {
            child_nodes.push_back(b.move(coord, infos));
            child_nodes[canput].value = calc_move_ordering_value(child_nodes[canput], cell_score);
            ++canput;
        }
    }

    // パスの処理 手番を交代して同じ深さで再帰する
    if (canput == 0) {
        // 2回連続パスなら評価関数を実行
        if (passed)
            return evaluate(b, cell_score);
        b.player = 1 - b.player;
        return -nega_scout_1(b, depth, true, -beta, -alpha, cell_score, infos);
    }

    // move ordering実行
    if (canput >= 2)
        sort(child_nodes.begin(), child_nodes.end());

    // まず最善手候補を通常窓で探索
    g = -nega_scout_1(child_nodes[0], depth - 1, false, -beta, -alpha, cell_score, infos);
    if (g >= beta) { // 興味の範囲よりもminimax値が上のときは枝刈り fail high
        if (g > l) {
            // 置換表の下限値に登録
            transpose_table_lower[b] = g;
        }
        return g;
    }
    alpha = max(alpha, g);
    max_score = max(max_score, g);

    // 残りの手をnull window searchを使って高速に探索
    for (int i = 1; i < canput; ++i) {
        // まずはnull window search
        g = -nega_alpha_transpose_1(child_nodes[i], depth - 1, false, -alpha - 1, -alpha, cell_score, infos);
        if (g >= beta) { // 興味の範囲よりもminimax値が上のときは枝刈り fail high
            if (g > l) {
                // 置換表の下限値に登録
                transpose_table_lower[b] = g;
            }
            return g;
        }
        if (g > alpha) { // 最善手候補よりも良い手が見つかった場合は再探索
            alpha = g;
            g = -nega_scout_1(child_nodes[i], depth - 1, false, -beta, -alpha, cell_score, infos);
            if (g >= beta) { // 興味の範囲よりもminimax値が上のときは枝刈り fail high
                if (g > l) {
                    // 置換表の下限値に登録
                    transpose_table_lower[b] = g;
                }
                return g;
            }
        }
        alpha = max(alpha, g);
        max_score = max(max_score, g);
    }
    if (max_score < alpha) { // fail-low ?
        // 置換表の下限値に登録 fail low
        transpose_table_upper[b] = max_score;
    } else {
        // minimax値が求まった
        transpose_table_upper[b] = max_score;
        transpose_table_lower[b] = max_score;
    }
    return max_score;
}

// depth手読みの探索
int search_1(board b, int depth, int cell_score[hw / 2][n_line], Infos infos) {
    visited_nodes = 0;
    transpose_table_upper.clear();
    transpose_table_lower.clear();
    former_transpose_table_upper.clear();
    former_transpose_table_lower.clear();
    // 子ノードを全列挙
    int coord, canput = 0;
    vector<board> child_nodes;
    for (coord = 0; coord < hw2; ++coord) {
        if (b.is_legal(coord, infos)) {
            child_nodes.push_back(b.move(coord, infos));
            ++canput;
        }
    }
    // 1手ずつ探索を深める
    int search_depth, res, score, alpha, beta, i;
    int start_depth = max(1, depth - 3); // 最初に探索する手数
    for (search_depth = start_depth; search_depth <= depth; ++search_depth) {
        alpha = -inf;
        beta = inf;
        if (canput >= 2) {
            // move orderingのための値を得る
            for (board &nb: child_nodes)
                nb.value = calc_move_ordering_value(nb, cell_score);
            // move ordering実行
            sort(child_nodes.begin(), child_nodes.end());
        }

        // 最善手候補を通常窓で探索
        score = -nega_scout_1(child_nodes[0], search_depth - 1, false, -beta, -alpha, cell_score, infos);
        alpha = score;
        res = child_nodes[0].policy;

        // 残りの手をnull window searchで探索
        for (i = 1; i < canput; ++i) {
            score = -nega_alpha_transpose_1(child_nodes[i], search_depth - 1, false, -alpha - 1, -alpha, cell_score, infos);
            // 最善手候補よりも良い手が見つかった
            if (alpha < score) {
                alpha = score;
                score = -nega_scout_1(child_nodes[i], search_depth - 1, false, -beta, -alpha, cell_score, infos);
                res = child_nodes[i].policy;
            }
            alpha = max(alpha, score);
        }
        cerr << "searched depth " << search_depth << " policy " << res << " visited nodes " << visited_nodes << endl;
        transpose_table_upper.swap(former_transpose_table_upper);
        transpose_table_upper.clear();
        transpose_table_lower.swap(former_transpose_table_lower);
        transpose_table_lower.clear();
    }
    return res;
}

int main() {
    //init();
    board_init();
    //evaluate_init();
    ArrStruct a = make_score();
    int arr[64];
    board b;
    int ai_player, policy;
    cin >> ai_player;
    Infos infos;
    while (true) {
        input_board(arr);
        b.translate_from_arr_1(arr, ai_player, infos);
        cerr << evaluate(b, a.cell_score) << endl;
        b.print();
        policy = search_1(b, 8, a.cell_score, infos);
        cout << policy / hw << " " << policy % hw << endl;
    }
    return 0;
}