#include "Chessboard.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEngine>

#include <iostream>

Chessboard::Chessboard(int size, QGraphicsView *gv) : QGraphicsScene(gv), size(size) {

    this->pm_back = new QPixmap(":/images/back");
    gv->setBackgroundBrush(pm_back->scaled(gv->width(), gv->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            QPixmap pm(32, 32);
            pm.fill(Qt::transparent);

            QPainter pter(&pm);
            pter.setPen(QPen(Qt::black, 2));
            pter.setBrush(Qt::red);
            pter.fillRect(pm.rect(), Qt::transparent);
            pter.drawEllipse(pm.width()/3, pm.height()/3, pm.width()/3, pm.height()/3);

            QGraphicsPixmapItem *gpi = new QGraphicsPixmapItem(pm);
            gpi->setPos(27 + pm.width()*j - pm.width()/2, 27 + pm.height()*i - pm.height()/2);

            this->addItem(gpi);
            this->pmi_redcircles.append(gpi);
        }
    }
}

Chessboard::~Chessboard() {
    delete this->pm_back;
    for (auto pmi : this->pmi_redcircles)
        delete pmi;
}

void Chessboard::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    std::cout << "X:" << event->scenePos().x() << " Y:" << event->scenePos().y() << std::endl;
}
