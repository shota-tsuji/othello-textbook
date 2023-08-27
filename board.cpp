#include "board.hpp"

void board_init() {
    int idx, b, w, place, i, j, k, l_place, inc_idx;
    for (idx = 0; idx < n_line; ++idx) {
        b = create_one_color(idx, 0);
        w = create_one_color(idx, 1);
        for (place = 0; place < hw; ++place) {
            move_arr[Black][idx][place][0] = move_line_half(b, w, place, 0);
            move_arr[Black][idx][place][1] = move_line_half(b, w, place, 1);
            if (move_arr[Black][idx][place][0] || move_arr[Black][idx][place][1])
                legal_arr[Black][idx][place] = true;
            else
                legal_arr[Black][idx][place] = false;
            move_arr[White][idx][place][0] = move_line_half(w, b, place, 0);
            move_arr[White][idx][place][1] = move_line_half(w, b, place, 1);
            if (move_arr[White][idx][place][0] || move_arr[White][idx][place][1])
                legal_arr[White][idx][place] = true;
            else
                legal_arr[White][idx][place] = false;
        }
        for (place = 0; place < hw; ++place) {
            flip_arr[Black][idx][place] = idx;
            flip_arr[White][idx][place] = idx;
            put_arr[Black][idx][place] = idx;
            put_arr[White][idx][place] = idx;
            if (b & (1 << (hw - 1 - place)))
                flip_arr[White][idx][place] += pow3_1[hw - 1 - place];
            else if (w & (1 << (hw - 1 - place)))
                flip_arr[Black][idx][place] -= pow3_1[hw - 1 - place];
            else {
                put_arr[Black][idx][place] -= pow3_1[hw - 1 - place] * 2;
                put_arr[White][idx][place] -= pow3_1[hw - 1 - place];
            }
        }
    }
    for (place = 0; place < hw2; ++place) {
        inc_idx = 0;
        for (idx = 0; idx < n_board_idx; ++idx) {
            for (l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    place_included[place][inc_idx++] = idx;
            }
        }
        if (inc_idx == 3)
            place_included[place][inc_idx] = -1;
    }
    for (idx = 0; idx < n_board_idx; ++idx) {
        for (place = 0; place < hw2; ++place) {
            local_place[idx][place] = -1;
            for (l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    local_place[idx][place] = l_place;
            }
        }
    }
    cerr << "board initialized" << endl;
}
