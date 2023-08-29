#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <iostream>
#include <vector>
#include "const.hpp"
#include "cell_evaluation.hpp"

using namespace std;


// インデックスからボードの1行/列をビットボードで生成する
int create_one_color(int idx, const int k);

// ビットボードにおける着手に使う
inline int trans(const int pt, const int k) {
    if (k == 0)
        return pt << 1;
    else
        return pt >> 1;
}

// ビットボードで1行/列において着手
inline int move_line_half(const int p, const int o, const int place, const int k) {
    int mask;
    int res = 0;
    int pt = 1 << (hw - 1 - place);
    if (pt & p || pt & o)
        return res;
    mask = trans(pt, k);
    while (mask && (mask & o)) { // not vacant and opponent stones are continued
        ++res;
        mask = trans(mask, k);
        if (mask & p)
            return res;
    }
    return 0; // If just opponent stones exist with vacant and self stones does not exist between them
}

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

void board_init();

class board {
public:
    int board_idx[n_board_idx]; // インデックス
    int player;                 // 盤面から打つ手番
    int policy;                 // 盤面に至る直前に打った手
    int value;                  // 盤面の仮の評価値(move orderingに使う)
    int n_stones;               // 石数

public:
    // move orderingでソートするためにオペレータをオーバーロード
    bool operator<(const board &another) const {
        return value > another.value;
    }

    // ハッシュテーブル(unordered_map)で使う同値判定
    bool operator==(const board &another) const {
        if (this->player != another.player)
            return false;
        for (int i = 0; i < hw; ++i) {
            if (this->board_idx[i] != another.board_idx[i])
                return false;
        }
        return true;
    }

    // ハッシュテーブル(unordered_map)で使う非同値判定
    bool operator!=(const board &another) const {
        return !(this->operator==(another));
    }

    // ハッシュテーブル(unordered_map)に使うハッシュ関数
    struct hash {
        typedef size_t result_type;

        // ハッシュテーブルで使うためのハッシュ関数
        // hash = sum(i=0からi=7)(インデックス[i] * 17^i)
        // 17を使うとやたら性能が良い。
        size_t operator()(const board &b) const {
            return
                    b.board_idx[0] +
                    b.board_idx[1] * 17 +
                    b.board_idx[2] * 289 +
                    b.board_idx[3] * 4913 +
                    b.board_idx[4] * 83521 +
                    b.board_idx[5] * 1419857 +
                    b.board_idx[6] * 24137549 +
                    b.board_idx[7] * 410338673;
        }
    };


    // ボードのコンソールへの表示
    // tests board output
    inline void print() {
        int i, j, tmp;
        string res;
        for (i = 0; i < hw; ++i) {
            tmp = this->board_idx[i];
            res = "";
            for (j = 0; j < hw; ++j) {
                if (tmp % 3 == 0)
                    res = "X " + res;
                else if (tmp % 3 == 1)
                    res = "O " + res;
                else
                    res = ". " + res;
                tmp /= 3;
            }
            cerr << res << endl;
        }
        cerr << endl;
    }

    // 合法手判定
    // tests in specific patterns for each board instance
    inline bool is_legal(int g_place, Infos infos) {
        bool res = false;
        for (int i = 0; i < 3; ++i) {
            int idx = infos.ii.place_included[g_place][i];
            res |= infos.li.legal_arr[this->player][this->board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }
        int idx = infos.ii.place_included[g_place][3];
        if (idx != -1) {
            res |= infos.li.legal_arr[this->player][this->board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }
        return res;
    }

    // 着手
    /*
    inline board move(const int g_place) {
        board res;
        for (int i = 0; i < n_board_idx; ++i)
            res.board_idx[i] = this->board_idx[i];
        move_p(&res, g_place, 0);
        move_p(&res, g_place, 1);
        move_p(&res, g_place, 2);
        if (place_included[g_place][3] != -1)
            move_p(&res, g_place, 3);
        for (int i = 0; i < 3; ++i)
            res.board_idx[place_included[g_place][i]] = put_arr[this->player][res.board_idx[place_included[g_place][i]]][local_place[place_included[g_place][i]][g_place]];
        if (place_included[g_place][3] != -1)
            res.board_idx[place_included[g_place][3]] = put_arr[this->player][res.board_idx[place_included[g_place][3]]][local_place[place_included[g_place][3]][g_place]];
        res.player = 1 - this->player;
        res.n_stones = this->n_stones + 1;
        res.policy = g_place;
        return res;
    }
     */
    inline board move(const int g_place, Infos infos) {
        board res;
        for (int i = 0; i < n_board_idx; ++i) {
            res.board_idx[i] = this->board_idx[i];
        }

        move_p(&res, g_place, 0, infos);
        move_p(&res, g_place, 1, infos);
        move_p(&res, g_place, 2, infos);
        if (infos.ii.place_included[g_place][3] != -1) {
            move_p(&res, g_place, 3, infos);
        }

        for (int i = 0; i < 3; ++i) {
            int idx = infos.ii.place_included[g_place][i];
            res.board_idx[idx] = infos.pi.put_arr[this->player][res.board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }
        int idx = infos.ii.place_included[g_place][3];
        if (idx != -1) {
            res.board_idx[idx] = infos.pi.put_arr[this->player][res.board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }

        res.player = 1 - this->player;
        res.n_stones = this->n_stones + 1;
        res.policy = g_place;
        return res;
    }

    // 一般的な配列形式からインデックス形式に変換
    // tests for 38 indexes, number of discs and player
    inline void translate_from_arr_1(const int arr[], int player, Infos infos) {
        int i, j;
        for (i = 0; i < n_board_idx; ++i)
            this->board_idx[i] = n_line - 1; // init all values with vacant eight cells (6560)
        this->n_stones = hw2; // init with all discs (64)
        for (i = 0; i < hw2; ++i) { // loop each cell
            for (j = 0; j < 4; ++j) { // loop each index (0<=pattern<4)
                const int index = infos.ii.place_included[i][j];
                const int cell = infos.local_info.local_place[index][i];
                if (index == -1)
                    continue;
                if (arr[i] == Black)
                    this->board_idx[index] -= 2 * pow3_1[hw - 1 - cell];
                else if (arr[i] == White)
                    this->board_idx[index] -= pow3_1[hw - 1 - cell];
                else if (j == 0)
                    --this->n_stones;
            }
        }
        this->player = player;
    }


    inline void translate_from_arr(std::vector<int> arr, int player, Infos infos) {
        int i, j;
        for (i = 0; i < n_board_idx; ++i)
            this->board_idx[i] = n_line - 1; // init all values with vacant eight cells (6560)
        this->n_stones = hw2; // init with all discs (64)
        for (i = 0; i < hw2; ++i) { // loop each cell
            for (j = 0; j < 4; ++j) { // loop each index (0<=pattern<4)
                const int index = infos.ii.place_included[i][j];
                const int cell = infos.local_info.local_place[index][i];
                if (index == -1)
                    continue;
                if (arr[i] == Black)
                    this->board_idx[index] -= 2 * pow3_1[hw - 1 - cell];
                else if (arr[i] == White)
                    this->board_idx[index] -= pow3_1[hw - 1 - cell];
                else if (j == 0)
                    --this->n_stones;
            }
        }
        this->player = player;
    }

private:
    // 石をひっくり返す
    inline void do_flip(board *res, int g_place, Infos infos) {
        for (int i = 0; i < 3; ++i) {
            int idx = infos.ii.place_included[g_place][i];
            res->board_idx[idx] = infos.fi.flip_arr[this->player][res->board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }
        int idx = infos.ii.place_included[g_place][3];
        if (idx != -1) {
            res->board_idx[idx] = infos.fi.flip_arr[this->player][res->board_idx[idx]][infos.local_info.local_place[idx][g_place]];
        }
    }

    // 石をひっくり返す
    inline void move_p(board *res, int g_place, int i, Infos infos) {
        const int idx = infos.ii.place_included[g_place][i];
        const int place = infos.local_info.local_place[idx][g_place];
        for (int j = 1; j <= infos.mi.move_arr[this->player][this->board_idx[idx]][place][0]; ++j) {
            // printf("left: move_p");
            do_flip(res, g_place - move_offset[idx] * j, infos);
        }
        for (int j = 1; j <= infos.mi.move_arr[this->player][this->board_idx[idx]][place][1]; ++j) {
            do_flip(res, g_place + move_offset[idx] * j, infos);
        }
    }
};

// Board coordinate constants for one dimensional array index (i.e. values are 0-63)
enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
};
int evaluate(board b, int cell_score[hw / 2][n_line]);
#endif //BOARD_H
