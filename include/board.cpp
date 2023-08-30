#include "board.hpp"
#include "const.hpp"
#include "cell_evaluation.hpp"

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

int evaluate(board b, Infos infos) {
    int res = 0, i;
    for (i = 0; i < hw / 2; ++i)
        res += infos.csi.cell_score[i][b.board_idx[i]];
    for (i = 0; i < hw / 2; ++i)
        // 折り返して配列確認している?
        res += infos.csi.cell_score[hw / 2 - 1 - i][b.board_idx[hw / 2 + i]];
    if (b.player == White)
        res = -res;
    return res;
}
