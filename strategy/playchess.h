//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_PLAYCHESS_H
#define GOBANG_PLAYCHESS_H

#include <ostream>
#include <QThread>

using std::ostream;

enum Direc {L, U, LB, LU};

struct position {
    int x = 0, y = 0;

    position();
    position(int x, int y);
    friend ostream &operator<<(ostream &out, const position &p);
};

class playchess : public QThread {  // black: 1  white: -1

    Q_OBJECT

public:

    playchess();

    int setChessman(position pos, const int side);
    int setChessman(position pos);
    position solve();
    int isDone(Direc *direc, position *pos);
    void restart();
    void regret(const position pos);
    int getSide();
    void setSearchDepth(int depth);
    int getRound() {return this->round;}

    constexpr static int size = 15;
    int curBlackScore = 0;
    int curWhiteScore = 0;

protected:
    void run();

signals:
    void resultReady(position pos);

private:
    int board[size][size] = {};
    int round = 0;
    int depth = 2;
};

#endif //GOBANG_CHESSBOARD_H
