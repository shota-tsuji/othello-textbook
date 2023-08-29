#include "cell_evaluation.hpp"
#include "board.hpp"
#include "const.hpp"

ArrStruct make_score() {
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
