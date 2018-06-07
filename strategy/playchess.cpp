#include <iostream>
#include <fstream>
#include "playchess.h"
#include "strategy/patternrecognizer.h"
extern "C" {
#include "gobang2.h"
}

using std::cout;
using std::endl;
using std::ostream;


playchess::playchess() : pr("patterns.txt"), round(0), depth(3) {
    qRegisterMetaType<Position>("Position");
    init_rules(NULL);
}

void playchess::reload() {
    init_rules(NULL);
    pr.initialize("patterns.txt");
}

int playchess::setChessman(Position pos, const int side) {

    cout << "No." << (round + 1) << " at (" << pos.first << ", " << pos.second << ") with " << (side == 1 ? "black." : "white.") << endl;

    if (pos.first <= this->size && pos.first > 0 &&
        pos.second <= this->size && pos.second > 0 && board[pos.first - 1][pos.second - 1] == 0) {

        this->board[pos.first - 1][pos.second - 1] = side;

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

int playchess::setChessman(Position pos) {
    return this->setChessman(pos, getSide());
}

Position playchess::solve() {  // here

    Position pos{-1, -1};
    bool flag = false;

    switch (solvemode) {
        case SolveMode::ruleBase: {
            try {
                pos = pr.query(this->board, getSide());
                break;
            } catch (int) {
                flag = true;
            }
        // 然后移交至searchBase
        }
        case SolveMode::searchBase: {
            Board *bd = bd_cre(this->board);
            auto rs = workout(bd, this->depth, NULL);
            pos.first = rs.x; pos.second = rs.y;
            break;
        }
    }

    if (flag) {
        std::ofstream out("unrecognized.txt", std::ofstream::app);
        std::ostream_iterator<std::string> coit(out);
        *coit++ = "\n[" + std::string(getSide() == -1 ? "Black" : "White")
                + " turns, round " + std::to_string(getRound() + 1) + ", recommand pos: ("
                + std::to_string(pos.first) + "," + std::to_string(pos.second) + ")]\n";
        for (auto i = 0; i < TS; ++i) {
            for (auto j = 0; j < TS; ++j) {
                    *coit++ = (i + 1 == pos.first && j + 1 == pos.second)
                        ? "x "
                        : (board[i][j] == 1 ? "● " : board[i][j] == -1 ? "○ " : "· ");
            }
            *coit++ = "\n";
        }
        std::cerr << "Recorded a state with unrecoginized pattern!!!" << std::endl;
        out.close();
    }

    //////////////////////////////////
    this->setChessman(pos);

    return pos;
}

int playchess::isDone(Direc *direc, Position *pos) {

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
    pos->first = i + 1; pos->second = j + 1;
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

void playchess::regret(const Position pos) {
    if (pos.first <= this->size && pos.first > 0 &&
        pos.second <= this->size && pos.second > 0 && board[pos.first - 1][pos.second - 1] != 0) {

        this->board[pos.first - 1][pos.second - 1] = 0;
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
    Position pos = this->solve();
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
