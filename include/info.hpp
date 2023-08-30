#ifndef OTHELLO_TEXTBOOK_INFO_H
#define OTHELLO_TEXTBOOK_INFO_H
#include "cell_evaluation.hpp"

struct LegalInfo {
    // legal_arr[プレイヤー][ボードのインデックス][マスの位置] = trueなら合法、falseなら非合法
    bool legal_arr[2][n_line][hw];
};
LegalInfo make_legal_arr(int move_arr[2][n_line][hw][2]);

struct MovementInfo {
    // move_arr[プレイヤー][ボードのインデックス][マスの位置][0: 左 1: 右] = 何マスひっくり返せるか
    int move_arr[2][n_line][hw][2];
};
MovementInfo make_movement();

struct FlipInfo {
    // flip_arr[プレイヤー][ボードのインデックス][マスの位置] = ボードのインデックスのマスの位置をひっくり返した後のインデックス
    int flip_arr[2][n_line][hw];
};
FlipInfo make_flip_info();

struct PutInfo {
    // put_arr[プレイヤー][ボードのインデックス][マスの位置] = ボードのインデックスのマスの位置に着手した後のインデックス
    int put_arr[2][n_line][hw];
};
PutInfo make_put_info();

struct IncludedInfo {
    // place_included[マスの位置] = そのマスが関わるインデックス番号の配列(3つのインデックスにしか関わらない場合は最後の要素に-1が入る)
    int place_included[hw2][4];
};
IncludedInfo make_included_info();

struct LocalInfo {
    // local_place[インデックス番号][マスの位置] = そのインデックス番号におけるマスのローカルな位置
    int local_place[n_board_idx][hw2];
};
LocalInfo make_local_info();

struct ArrStruct {
    int cell_score[hw / 2][n_line];
};

// 盤面のインデックス(行のインデックス)において黒番目線のスコアを前計算しておく
//inline ArrStruct make_score() {
ArrStruct make_score();

class Infos {
public:
    LegalInfo li;
    MovementInfo mi;
    ArrStruct csi;
    FlipInfo fi;
    PutInfo pi;
    IncludedInfo ii;
    LocalInfo local_info;
    Infos();
};

#endif //OTHELLO_TEXTBOOK_INFO_H
