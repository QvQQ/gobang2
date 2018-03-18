#include "Chessboard.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEngine>
#include <QList>
#include "struct/Chessman.h"

#include <iostream>

Chessboard::Chessboard(int size, QGraphicsView *gv) : QGraphicsScene(gv), size(size) {

    this->pm_back = new QPixmap(":/images/back");
    gv->setBackgroundBrush(pm_back->scaled(gv->width(), gv->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    for (int i = 0; i < this->size; ++i) {
        QList<Chessman *> temp;
        for (int j = 0; j < this->size; ++j) {

            int w = 32, h = 32;
            Chessman *gcm = new Chessman(w, h);
            gcm->setPos(27 + w*j - w/2, 27 + h*i - h/2);

            this->addItem(gcm);
            temp.append(gcm);
        }
        this->pmi_chessmen.append(temp);
    }
}

Chessboard::~Chessboard() {
    delete this->pm_back;
    for (auto &pmi : this->pmi_chessmen)
        for (auto &pmii : pmi)
            delete pmii;
}

void Chessboard::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    std::cout << "X:" << event->scenePos().x() << " Y:" << event->scenePos().y() << std::endl;

    this->sendEvent(this->itemAt(event->pos(), QTransform()), event);

    QGraphicsScene::mousePressEvent(event);
}
