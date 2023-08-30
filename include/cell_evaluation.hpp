#ifndef CELL_EVALUATION_H
#define CELL_EVALUATION_H
#pragma once

#include <iostream>
#include "const.hpp"
//#include "board.hpp"

using namespace std;

const int cell_weight[hw2] = {
        30, -12, 0, -1, -1, 0, -12, 30,
        -12, -15, -3, -3, -3, -3, -15, -12,
        0, -3, 0, -1, -1, 0, -3, 0,
        -1, -3, -1, -1, -1, -1, -3, -1,
        -1, -3, -1, -1, -1, -1, -3, -1,
        0, -3, 0, -1, -1, 0, -3, 0,
        -12, -15, -3, -3, -3, -3, -15, -12,
        30, -12, 0, -1, -1, 0, -12, 30
};


#endif //CELL_EVALUATION_H
