//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include "../struct/actor.h"
#include <QGraphicsScene>

class chessboard : public actor {

public:

    chessboard(QGraphicsScene *gScene, string name, int size);
    ~chessboard();

    virtual int doDraw();
    virtual void doHide();

    void setSize(int size);
    int  getSize();
    void resize(int size);

private:
    QGraphicsScene *gScene;
    int size;
};

#endif //GOBANG_CHESSBOARD_H
