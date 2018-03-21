//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_PLAYCHESS_H
#define GOBANG_PLAYCHESS_H

#include <ostream>

using std::ostream;

struct position {
    int x = 0, y = 0;

    position(int x, int y);
    friend ostream &operator<<(ostream &out, const position &p);
};

class playchess {  // black: 1  white: -1

public:

    playchess();

    int setChessman(position pos, const int side);
    int setChessman(position pos);
    position solve(); // temporary

    int getSide();

    constexpr static int size = 15;

private:
    int board[size][size] = {};
    int round;
};

#endif //GOBANG_CHESSBOARD_H
