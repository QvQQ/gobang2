//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSMAN_H
#define GOBANG_CHESSMAN_H

#include "../struct/actor.h"
#include <QGraphicsPixmapItem>

class chessman : public QGraphicsPixmapItem, public actor {

public:

    chessman(string name, position pos);
    ~chessman();

    virtual int doDraw();
    virtual void doHide();
};

#endif //GOBANG_CHESSMAN_H
