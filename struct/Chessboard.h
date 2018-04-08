//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

class Chessboard : public QGraphicsScene{

public:

    Chessboard(QGraphicsView *gv, QLabel *label_black, QLabel *label_white, QLabel *label_round, QLabel *label_scoreOfCom, QLabel *label_scoreOfMan, QCheckBox *checkBox_blackReverse);
    ~Chessboard();

    void updateScore();
    void updateRound();
    void finish(Direc direc, position pos);

    void searchDepthChanged(int index);
    void displayStepsChanges(bool b);
    void blackReverseChanges(bool b);
    void restart();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    enum {thinking, waiting, idling} state = waiting;

private:

    void handleResult(position pos);

    playchess player;
    QLabel *label_black;
    QLabel *label_white;
    QLabel *label_round;
    QLabel *label_scoreOfCom;
    QLabel *label_scoreOfMan;
    QCheckBox *checkBox_blackReverse;
    int scoreOfCom = 0, scoreOfMan = 0;

    QPixmap *pm_back;
    QGraphicsPixmapItem *pmi_redcircle;
    QGraphicsLineItem *pmi_winLine = nullptr;
    QList<QList<Chessman *> > pmi_chessmen;

    Chessman *lastMan;
    Chessman::State sideOfCom = Chessman::White;
    Chessman::State sideOfMan = Chessman::Black;
};

#endif //GOBANG_CHESSBOARD_H
