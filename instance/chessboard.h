//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include "../struct/actor.h"

class chessboard : public actor {

public:

    chessboard(string name, position pos);
    ~chessboard();

    virtual int doDraw();
    virtual void doHide();
};

#endif //GOBANG_CHESSBOARD_H
