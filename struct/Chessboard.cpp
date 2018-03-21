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
#include "strategy/playchess.h"

#include <iostream>

Chessboard::Chessboard(QGraphicsView *gv) : QGraphicsScene(gv) {
    int w = 32, h = 32;
    this->pm_back = new QPixmap(":/images/back");
    gv->setBackgroundBrush(pm_back->scaled(gv->width(), gv->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ///////////
    auto Q = QPixmap(w, h);
    Q.fill(Qt::transparent);
    QPainter pter(&Q);
    pter.setPen(QPen(Qt::black, 1));
    pter.setBrush(Qt::red);
    pter.fillRect(Q.rect(), Qt::transparent);
    pter.setRenderHint(QPainter::Antialiasing);
    pter.drawEllipse(w/3.0, h/3.0, w/3.0, h/3.0);
    this->pmi_redcircle = this->addPixmap(Q);
    this->pmi_redcircle->setPos(-20, -20);
    ///////////
    for (int i = 0; i < this->player.size; ++i) {
        QList<Chessman *> temp;
        for (int j = 0; j < this->player.size; ++j) {
            Chessman *gcm = new Chessman(QRect(i + 1, j + 1, w, h));
            gcm->setPos(26.5 + w*j - w/2.0, 26.5 + h*i - h/2.0);
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

    QGraphicsItem *item = this->itemAt(event->scenePos(), QTransform());

    if (this->state == waiting && item && item->type() == 65535 + 233) {
        this->lastMan = dynamic_cast<Chessman *>(item);
        if (this->lastMan->getState() == Chessman::RedCircle) {
            this->state = thinking;
            this->lastMan->setState(this->lastVal);
            this->player.setChessman({this->lastMan->getPos().x(), this->lastMan->getPos().y()}, this->lastVal);

            this->pmi_redcircle->setPos(this->lastMan->scenePos());
            this->pmi_redcircle->setZValue(233);

            // start a new thread and solve
            position rspos = player.solve();
            this->lastMan = this->pmi_chessmen[rspos.x - 1][rspos.y - 1];
            this->lastMan->setState(static_cast<Chessman::State>(-this->lastVal));

            this->pmi_redcircle->setPos(this->lastMan->scenePos());
            this->pmi_redcircle->setZValue(233);

            this->state = waiting;
        }
    }
    QGraphicsScene::mousePressEvent(event);
}
