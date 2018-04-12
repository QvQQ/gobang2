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
    std::cerr << "wrong." << endl;
    return 0;
}

int playchess::setChessman(position pos) {
    return this->setChessman(pos, getSide());
}

position playchess::solve() {

    Board *bd = bd_cre(this->board);
    Point pos = workout(bd, this->depth, NULL);
    this->setChessman({pos.x, pos.y});

    return {pos.x, pos.y};
}

int playchess::isDone(Direc *direc, position*pos) {

    int (*p)[15] = this->board;

    int i, j, k, sum, n = -1;
    for (i = 0; i < TS; ++i) {
        for (j = 0; j < TS; ++j) {
            if (!p[i][j] && !(n = p[i][j])) continue;
            // row:
            if (j <= TS - CON) {
                for (k = sum = 0; k < CON; ++k)
                    sum += p[i][j + k];
                if (abs(sum) == CON) {
                    *direc = L;
                    goto rs;
                }
            }
            // col:
            if (i <= TS - CON) {
                for (k = sum = 0; k < CON; ++k)
                    sum += p[i + k][j];
                if (abs(sum) == CON) {
                    *direc = U;
                    goto rs;
                }
            }
            // sla:
            if (i >= CON - 1 && j <= TS - CON) {
                for (k = sum = 0; k < CON; ++k)
                    sum += p[i - k][j + k];
                if (abs(sum) == CON) {
                    *direc = LB;
                    goto rs;
                }
            }
            // bsla:
            if (i <= TS - CON && j <= TS - CON) {
                for (k = sum = 0; k < CON; ++k)
                    sum += p[i + k][j + k];
                if (abs(sum) == CON) {
                    *direc = LU;
                    goto rs;
                }
            }
        }
    }
    return abs(0);
rs:
    pos->x = i + 1; pos->y = j + 1;
    printf("Done at (%d, %d)\n", i + 1, j + 1);
    return 1;
}

void playchess::restart() {
    if (this->isRunning())
        terminate();
    this->round = 0;
    this->curBlackScore = this->curWhiteScore = 0;
    memset(this->board, 0, sizeof(this->board));
}

void playchess::regret(const position pos) {
    if (pos.x <= this->size && pos.x > 0 &&
        pos.y <= this->size && pos.y > 0 && board[pos.x - 1][pos.y - 1] != 0) {

        this->board[pos.x - 1][pos.y - 1] = 0;
        --this->round;

        Board *bd = bd_cre(this->board);
        evaluate(bd);
        extern int blackScore, whiteScore;
        this->curBlackScore = blackScore;
        this->curWhiteScore = whiteScore;

        return;
    }
    std::cerr << "wrong!" << endl;
}

void playchess::run() {
    position pos = this->solve();
    if (this->isRunning())
        emit this->resultReady(pos);
}

int playchess::getSide() {

    int sum = 0;
    for (auto &row : this->board)
        for (auto &col : row)
            sum += col;
    return sum == 1 ? -1 : 1;
}

void playchess::setSearchDepth(int depth) {
    this->depth = depth;
}
