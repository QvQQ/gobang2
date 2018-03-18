//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include "struct/Chessman.h"

class Chessboard : public QGraphicsScene{

public:

    Chessboard(int size, QGraphicsView *gv);
    ~Chessboard();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int size;
    QPixmap *pm_back;
    QList<QList<Chessman *> > pmi_chessmen;
};

#endif //GOBANG_CHESSBOARD_H
