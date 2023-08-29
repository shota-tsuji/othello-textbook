#include "board.hpp"
#include "const.hpp"
#include "cell_evaluation.hpp"

Infos::Infos() {
    mi = make_movement();
    li = make_legal_arr(mi.move_arr);
    csi = make_score();
    fi = make_flip_info();
    pi = make_put_info();
    ii = make_included_info();
    local_info = make_local_info();
}

int create_one_color(int idx, const int k) {
    int res = 0;
    for (int i = 0; i < hw; ++i) {
        if (idx % 3 == k) {
            res |= 1 << i;
        }
        idx /= 3;
    }
    return res;
}

void board_init() {


    cerr << "board initialized" << endl;
}
int evaluate(board b, int cell_score[hw / 2][n_line]) {
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
