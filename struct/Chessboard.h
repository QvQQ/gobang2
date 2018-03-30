//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include <QLabel>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

class Chessboard : public QGraphicsScene{

public:

    Chessboard(QGraphicsView *gv, QLabel *label);
    ~Chessboard();

    void updateScore();
    void finish(Direc direc, position pos);

    void restart();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:

    void handleResult(position pos);

    playchess player;

    QLabel *scoreLabel;
    QPixmap *pm_back;
    QGraphicsPixmapItem *pmi_redcircle;
    QGraphicsLineItem *pmi_winLine = nullptr;
    QList<QList<Chessman *> > pmi_chessmen;
    Chessman *lastMan;

    enum {thinking, waiting, idling} state = waiting;
    Chessman::State lastVal = Chessman::Black;
};

#endif //GOBANG_CHESSBOARD_H
