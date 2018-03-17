#include "Chessboard.h"
#include <QGraphicsScene>
#include <QGraphicsView>

Chessboard::Chessboard(int size, QGraphicsView *gv) : QGraphicsScene(gv), size(size) {

    QPixmap *pm = new QPixmap(":/images/back");
    *pm = pm->scaled(gv->width(), gv->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->addPixmap(*pm);
}

Chessboard::~Chessboard() {
    ;
}
