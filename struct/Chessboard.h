//
// Created by cat on 18-1-31.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QGraphicsScene>

class Chessboard : public QGraphicsScene{

public:

    Chessboard(int size, QGraphicsView *gv);
    ~Chessboard();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int size;
    QPixmap *pm_back;
    QList<QGraphicsPixmapItem*> pmi_redcircles;
};

#endif //GOBANG_CHESSBOARD_H
