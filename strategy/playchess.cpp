#include <iostream>
#include "playchess.h"
extern "C" {
#include "gobang2.h"
}

using std::cout;
using std::endl;
using std::ostream;

position::position() : x(0), y(0) {}
position::position(int x, int y) : x(x), y(y) {}

ostream &operator<<(ostream &out, const position &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

playchess::playchess() : round(0) {
    qRegisterMetaType<position>("position");
    init_rules(NULL);
}

int playchess::setChessman(position pos, const int side) {

    cout << "No." << (round + 1) << " at " << pos << " with " << (side == 1 ? "black." : "white.") << endl;

    if (pos.x <= this->size && pos.x > 0 &&
        pos.y <= this->size && pos.y > 0 && board[pos.x - 1][pos.y - 1] == 0) {

        this->board[pos.x - 1][pos.y - 1] = side;

        Board *bd = bd_cre(this->board);
        evaluate(bd);
        extern int blackScore, whiteScore;
        this->curBlackScore = blackScore;
        this->curWhiteScore = whiteScore;

        return ++round;
    }
    cout << "wrong." << endl;
    return 0;
}

int playchess::setChessman(position pos) {
    int re = this->setChessman(pos, getSide());
    return re;
}

position playchess::solve() {

    Board *bd = bd_cre(this->board);
    Point pos = workout(bd, DEP, NULL);
    this->setChessman({pos.x, pos.y});

    return {pos.x, pos.y};
}

int playchess::isDone(position pos) {
    Board *bd = bd_cre(this->board);
    return isfinish(bd, pos.x - 1, pos.y - 1);
}

void playchess::run() {
    emit this->resultReady(this->solve());
}

int playchess::getSide() {

    int sum = 0;
    for (auto &row : this->board)
        for (auto &col : row)
            sum += col;
    return sum == 0 ? 1 : -1;
}
