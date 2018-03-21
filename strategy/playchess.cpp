#include <iostream>
#include "playchess.h"
extern "C" {
#include "gobang2.h"
}

using std::cout;
using std::endl;
using std::ostream;

position::position(int x, int y) : x(x), y(y) {}

ostream &operator<<(ostream &out, const position &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

playchess::playchess() : round(0) {
    ;
}

int playchess::setChessman(position pos, const int side) {

    cout << "No." << (round + 1) << " at " << pos << " with " << (side == 1 ? "black." : "white.") << endl;

    if (pos.x <= this->size && pos.x > 0 &&
        pos.y <= this->size && pos.y > 0 && board[pos.x - 1][pos.y - 1] == 0) {

        this->board[pos.x - 1][pos.y - 1] = side;
        return ++round;
    }
    cout << "wrong." << endl;
    return 0;
}

int playchess::setChessman(position pos) {
    return this->setChessman(pos, getSide());
}

position playchess::solve() {  // temporary, no AI

    Board *bd = bd_cre(this->board);
    Point pos = workout(bd, DEP, NULL);
    this->setChessman({pos.x, pos.y});

    return {pos.x, pos.y};
//    for(int i = 0; i < this->size; ++i)
//        for(int j = 0; j < this->size; ++j)
//            if(!this->board[i][j]) {
//                this->setChessman({i + 1, j + 1});
//                return {i + 1, j + 1};
//            }
//    return {-1, -1};
}

int playchess::getSide() {

    int sum = 0;
    for (auto &row : this->board)
        for (auto &col : row)
            sum += col;
    return sum == 0 ? 1 : -1;
}
