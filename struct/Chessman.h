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

    State getState() const;
    void  setState(State state);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    int type() const;

    QPainterPath shape() const;

    QPoint getPos() const;

private:
    State state;
    QPoint pos;

    struct {
        QPixmap none;
        QPixmap redcircle;
        QPixmap white;
        QPixmap black;
    } pm;

    QPainterPath ppshape;
};

#endif //GOBANG_CHESSMAN_H
