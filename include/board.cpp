#include "board.hpp"
#include "const.hpp"
#include "cell_evaluation.hpp"

MovementInfo make_movement() {
    MovementInfo mi;

    for (int idx = 0; idx < n_line; ++idx) {
        int b = create_one_color(idx, 0);
        int w = create_one_color(idx, 1);
        for (int place = 0; place < hw; ++place) {
            mi.move_arr[Black][idx][place][0] = move_line_half(b, w, place, 0);
            mi.move_arr[Black][idx][place][1] = move_line_half(b, w, place, 1);
            mi.move_arr[White][idx][place][0] = move_line_half(w, b, place, 0);
            mi.move_arr[White][idx][place][1] = move_line_half(w, b, place, 1);
        }
    }

    return mi;
}

FlipInfo make_flip_info() {
    FlipInfo fi;
    for (int idx = 0; idx < n_line; ++idx) {
        int b = create_one_color(idx, 0);
        int w = create_one_color(idx, 1);
        for (int place = 0; place < hw; ++place) {
            fi.flip_arr[Black][idx][place] = idx;
            fi.flip_arr[White][idx][place] = idx;
            if (b & (1 << (hw - 1 - place)))
                fi.flip_arr[White][idx][place] += pow3_1[hw - 1 - place];
            else if (w & (1 << (hw - 1 - place)))
                fi.flip_arr[Black][idx][place] -= pow3_1[hw - 1 - place];
        }
    }

    return fi;
}

PutInfo make_put_info() {
    PutInfo pi;
    for (int idx = 0; idx < n_line; ++idx) {
        int b = create_one_color(idx, 0);
        int w = create_one_color(idx, 1);
        for (int place = 0; place < hw; ++place) {
            pi.put_arr[Black][idx][place] = idx;
            pi.put_arr[White][idx][place] = idx;
            if (b & (1 << (hw - 1 - place))) {}
            else if (w & (1 << (hw - 1 - place))) {}
            else {
                pi.put_arr[Black][idx][place] -= pow3_1[hw - 1 - place] * 2;
                pi.put_arr[White][idx][place] -= pow3_1[hw - 1 - place];
            }
        }
    }

    return pi;
}

LocalInfo make_local_info() {
    LocalInfo local_info;

    for (int idx = 0; idx < n_board_idx; ++idx) {
        for (int place = 0; place < hw2; ++place) {
            local_info.local_place[idx][place] = -1;
            for (int l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    local_info.local_place[idx][place] = l_place;
            }
        }
    }

    return local_info;
}

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

IncludedInfo make_included_info() {
    IncludedInfo ii;

    for (int place = 0; place < hw2; ++place) {
        int inc_idx = 0;
        for (int idx = 0; idx < n_board_idx; ++idx) {
            for (int l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    ii.place_included[place][inc_idx++] = idx;
            }
        }
        if (inc_idx == 3)
            ii.place_included[place][inc_idx] = -1;
    }

    return ii;
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
