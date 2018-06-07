//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_PLAYCHESS_H
#define GOBANG_PLAYCHESS_H

#include <ostream>
#include <QThread>
#include "strategy/patternrecognizer.h"

using std::ostream;

enum Direc {L, U, LB, LU};
enum class SolveMode {ruleBase, searchBase};

using Position = std::pair<int, int>;

class playchess : public QThread {  // black: 1  white: -1

    Q_OBJECT

public:

    playchess();

    void reload();
    int setChessman(Position pos, const int side);
    int setChessman(Position pos);
    Position solve();
    int isDone(Direc *direc, Position *pos);
    void restart();
    void regret(const Position pos);
    int getSide();
    void setSearchDepth(int depth) { this->depth = depth; }
    int getRound() { return round; }

    void setMode(SolveMode sm) { solvemode = sm; }

    constexpr static int size = 15;
    int curBlackScore = 0;
    int curWhiteScore = 0;

protected:
    void run();

signals:
    void resultReady(Position pos);

private:
    PatternRecognizer pr;
    SolveMode solvemode = SolveMode::searchBase;
    int board[size][size] = {};
    int round;
    int depth;
};

#endif //GOBANG_CHESSBOARD_H
