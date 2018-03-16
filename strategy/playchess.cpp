#include <iostream>
#include "playchess.h"

using std::clog;
using std::endl;

int chessboard::setChessman(position pos) {

    clog << "No." << (round + 1) << " at " << &pos << " with ";

    if (pos.x < this->size && pos.x >= 0 &&
            pos.y < this->size && pos.y >= 0 && board[pos.x][pos.y] == 0) {

        this->board[pos.x][pos.y] = this->getSide();
        return ++round;
    }
    clog << "wrong." << endl;
    return 0;
}

position chessboard::solve() {  // temporary, no AI

    for(int i = 0; i < this->size; ++i)
        for(int j = 0; j < this->size; ++j)
            if(!this->board[i][j])
                return {i, j};
    return {-1, -1};
}

int chessboard::getSide() {

    int sum = 0;
    for (auto &row : this->board)
        for (auto &col : row)
            sum += col;
    clog << (-sum == 1 ? "black." : "white.") << endl;
    return -sum;
}

int chessboard::round = 0;
