//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <ostream>

using std::ostream;

struct position {
    int x = 0, y = 0;

    position(int x, int y);
    friend ostream &operator<<(ostream &out, const position &p);
};

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
