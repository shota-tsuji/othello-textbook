#include "board.hpp"

LegalInfo make_legal_arr(int move_arr[2][n_line][hw][2]) {
    LegalInfo li;
    for (int idx = 0; idx < n_line; ++idx) {
        for (int place = 0; place < hw; ++place) {
            if (move_arr[Black][idx][place][0] || move_arr[Black][idx][place][1])
                li.legal_arr[Black][idx][place] = true;
            else
                legal_arr[Black][idx][place] = false;
            if (move_arr[White][idx][place][0] || move_arr[White][idx][place][1])
                li.legal_arr[White][idx][place] = true;
            else
                li.legal_arr[White][idx][place] = false;
        }
    }

    return li;
}

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

Infos::Infos() {
    mi = make_movement();
    li = make_legal_arr(mi.move_arr);
    csi = make_score();
}

void board_init() {

    for (int idx = 0; idx < n_line; ++idx) {
        int b = create_one_color(idx, 0);
        int w = create_one_color(idx, 1);
        for (int place = 0; place < hw; ++place) {
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

    for (int place = 0; place < hw2; ++place) {
        int inc_idx = 0;
        for (int idx = 0; idx < n_board_idx; ++idx) {
            for (int l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    place_included[place][inc_idx++] = idx;
            }
        }
        if (inc_idx == 3)
            place_included[place][inc_idx] = -1;
    }

    for (int idx = 0; idx < n_board_idx; ++idx) {
        for (int place = 0; place < hw2; ++place) {
            local_place[idx][place] = -1;
            for (int l_place = 0; l_place < hw; ++l_place) {
                if (global_place[idx][l_place] == place)
                    local_place[idx][place] = l_place;
            }
        }
    }
    cerr << "board initialized" << endl;
}
