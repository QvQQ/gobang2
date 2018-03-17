#include "chessboard.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

chessboard::chessboard(QGraphicsScene *gScene, string name, int size) : actor(name, position(0, 0)), gScene(gScene), size(size) {

    //QGraphicsEllipseItem *ellitem;
    //ellitem = this->gScene->addEllipse(23, 23, 200, 200, QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
    //ellitem->setVisible(false);

    QPixmap *pm = new QPixmap(":/images/back");
    *pm = pm->scaled(static_cast<QGraphicsView*>(this->gScene->parent())->width(),
                     static_cast<QGraphicsView*>(this->gScene->parent())->height(),
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);
    pixitem = this->gScene->addPixmap(*pm);
}

chessboard::~chessboard() {
    ;
}

void chessboard::setSize(int size) {
    this->size = size;
}

int chessboard::getSize() {
    return this->getSize();
}

void chessboard::resize(int size) {

}

int chessboard::doDraw() {

//    QGraphicsScene *scene = new QGraphicsScene(this);
//    scene->addEllipse(23, 23, 100, 100, QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
//    this->ui->graphicsView->setScene(scene);

    return actor::doDraw();
}

void chessboard::doHide() {
    return actor::doHide();
}
