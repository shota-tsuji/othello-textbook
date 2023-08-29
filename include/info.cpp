#include "const.hpp"
#include "info.hpp"
#include "cell_evaluation.hpp"

LegalInfo make_legal_arr(int move_arr[2][n_line][hw][2]) {
    LegalInfo li;
    for (int idx = 0; idx < n_line; ++idx) {
        for (int place = 0; place < hw; ++place) {
            if (move_arr[Black][idx][place][0] || move_arr[Black][idx][place][1])
                li.legal_arr[Black][idx][place] = true;
            else
                li.legal_arr[Black][idx][place] = false;
            if (move_arr[White][idx][place][0] || move_arr[White][idx][place][1])
                li.legal_arr[White][idx][place] = true;
            else
                li.legal_arr[White][idx][place] = false;
        }
    }

    return li;
}
