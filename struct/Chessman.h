//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSMAN_H
#define GOBANG_CHESSMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>

class Chessman : public QGraphicsPixmapItem{

public:

    Chessman(QRect initpos);
    ~Chessman();

    enum State {None = 0, RedCircle = 2, White = -1, Black = 1};
    QGraphicsPixmapItem pm_stepIndicate;

    State getState() const;
    void  setState(State state);

    void setStep(int stepCount);
    void clearStep();
    void setStepVisble(bool b);
    QGraphicsItem *getStepItem();

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    int type() const;

    QPainterPath shape() const;

    QPoint getPos() const;

private:
    State state;
    QPoint pos;
    int stepCount = 0;

    struct {
        QPixmap none;
        QPixmap redcircle;
        QPixmap white;
        QPixmap black;
    } pm;

    QPainterPath ppshape;
};

#endif //GOBANG_CHESSMAN_H
