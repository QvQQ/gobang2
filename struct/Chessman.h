//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSMAN_H
#define GOBANG_CHESSMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>

class Chessman : public QGraphicsPixmapItem{

public:

    Chessman(int w, int h);
    ~Chessman();

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QPainterPath shape() const;

private:
    enum State{None, Redcircle, White, Black};
    State state;

    struct {
        QPixmap none;
        QPixmap redcircle;
        QPixmap white;
        QPixmap black;
    } pm;

    QPainterPath ppshape;
};

#endif //GOBANG_CHESSMAN_H
