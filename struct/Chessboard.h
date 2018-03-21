//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

class Chessboard : public QGraphicsScene{

public:

    Chessboard(QGraphicsView *gv);
    ~Chessboard();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:

    playchess player;

    QPixmap *pm_back;
    QGraphicsPixmapItem *pmi_redcircle;
    QList<QList<Chessman *> > pmi_chessmen;
    Chessman *lastMan;

    enum {thinking, waiting} state = waiting;
    Chessman::State lastVal = Chessman::Black;
};

#endif //GOBANG_CHESSBOARD_H
