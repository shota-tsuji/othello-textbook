#ifndef OTHELLO_TEXTBOOK_INFO_H
#define OTHELLO_TEXTBOOK_INFO_H

struct LegalInfo {
    // legal_arr[プレイヤー][ボードのインデックス][マスの位置] = trueなら合法、falseなら非合法
    bool legal_arr[2][n_line][hw];
};
LegalInfo make_legal_arr(int move_arr[2][n_line][hw][2]);

#endif //OTHELLO_TEXTBOOK_INFO_H
