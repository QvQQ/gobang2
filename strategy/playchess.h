//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include "../struct/position.h"

class chessboard {  // black: 1  white: -1

public:

    int setChessman(position pos);
    position solve(); // temporary

private:

    int getSide();

    constexpr static int size = 15;
    int board[size][size] = {};
    static int round;
};

#endif //GOBANG_CHESSBOARD_H
