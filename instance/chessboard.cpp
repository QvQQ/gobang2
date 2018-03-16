#include "chessboard.h"
#include <QGraphicsScene>

chessboard::chessboard(QGraphicsScene *gScene, string name, int size) : actor(name, position(0, 0)), gScene(gScene), size(size) {

    this->gScene->addEllipse(23, 23, 200, 200, QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
    //this->
    //this->gView->setSceneRect();
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
