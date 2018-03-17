//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Chessboard : public QGraphicsScene{

public:

    Chessboard(int size, QGraphicsView *gv);
    ~Chessboard();

private:
    int size;
};

#endif //GOBANG_CHESSBOARD_H
