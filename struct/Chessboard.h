//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>
#include <QLabel>
#include <QLCDNumber>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

using std::vector;

class Chessboard : public QGraphicsScene{

public:

    Chessboard(QGraphicsView *gv, QLabel *label_black, QLabel *label_white, QLCDNumber *lcdNumber_round, QLabel *label_scoreOfCom, QLabel *label_scoreOfMan, QCheckBox *checkBox_blackReverse, QPushButton *button_regret);
    ~Chessboard();

    void updateScore();
    void updateRound();
    void finish(Direc direc, position pos);

    void searchDepthChanged(int index);
    void displayStepsChanges(bool b);
    void blackReverseChanges(bool b);
    void restart();
    void regret();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    enum PS {thinking, waiting, idling} playState = waiting;

private:

    void handleResult(position pos);

    playchess player;
    QLabel *label_black = nullptr;
    QLabel *label_white = nullptr;
    QLCDNumber *lcdNumber_round = nullptr;
    QLabel *label_scoreOfCom = nullptr;
    QLabel *label_scoreOfMan = nullptr;
    QCheckBox *checkBox_blackReverse = nullptr;
    int scoreOfCom = 0, scoreOfMan = 0;
    QPushButton *button_regret = nullptr;

    QPixmap *pm_back = nullptr;
    QGraphicsPixmapItem *pmi_redcircle = nullptr;
    QGraphicsLineItem *pmi_winLine = nullptr;
    QList<QList<Chessman *> > pmi_chessmen;

    Chessman *lastMan = nullptr;
    Chessman::State sideOfCom = Chessman::White;
    Chessman::State sideOfMan = Chessman::Black;

    struct stu_stepState {
        Chessman *curMan;
        Chessman *lastMan;
    };
    vector <stu_stepState> stepState;
};

#endif //GOBANG_CHESSBOARD_H

















