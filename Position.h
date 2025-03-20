//
// Created by Gabriele Preti on 09/03/25.
//

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
using namespace std;
#include "Constant.h"


class Position {
protected:
    int coord[snake_length][2];
public:
    Position();
    void debug();

    void Shift();

    void Push(int row_d, int col_d);

    void Pop();

    bool Dups();
};



#endif //POSITION_H
