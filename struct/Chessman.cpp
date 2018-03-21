#include "Chessman.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QPainterPath>
#include <iostream>

Chessman::Chessman(QRect initpos) : state(this->None){

    this->setAcceptHoverEvents(true);
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    this->pos.setX(initpos.x());
    this->pos.setY(initpos.y());

    /////////////// pm.none
    this->pm.none = QPixmap(initpos.width(), initpos.height());
    this->pm.none.fill(Qt::transparent);

    /////////////// pm.redcircle
    this->pm.redcircle = QPixmap(initpos.width(), initpos.height());
    this->pm.redcircle.fill(Qt::transparent);

    QPainter pter(&this->pm.redcircle);
    pter.setPen(QPen(Qt::black, 2));
    pter.setBrush(Qt::red);
    pter.fillRect(this->pm.redcircle.rect(), Qt::transparent);
    pter.setRenderHint(QPainter::Antialiasing);
    pter.drawEllipse(initpos.width()/3.0, initpos.height()/3.0, initpos.width()/3.0, initpos.height()/3.0);

    /////////////// pm.black
    this->pm.black = QPixmap(":/images/black");
    this->pm.black = this->pm.black.scaled(initpos.width()*0.9, initpos.height()*0.9, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->ppshape.addEllipse(this->pm.black.rect());

    /////////////// pm.white
    this->pm.white = QPixmap(":/images/white");
    this->pm.white = this->pm.white.scaled(initpos.width()*0.9, initpos.height()*0.9, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    /////////////// set default
    this->setPixmap(this->pm.none);
}

Chessman::~Chessman() {
    ;
}

Chessman::State Chessman::getState() const{
    return this->state;
}

void Chessman::setState(State state) {
    switch (state) {
        case Black:
            this->setPixmap(this->pm.black);     break;
        case White:
            this->setPixmap(this->pm.white);     break;
        case None:
            this->setPixmap(this->pm.none);      break;
        case RedCircle:
            this->setPixmap(this->pm.redcircle); break;
    }
    this->state = state;
}

void Chessman::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    if (this->state == this->None) {  // None -> Redcircle
        this->setState(this->RedCircle);
    }
}

void Chessman::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    if (this->state == this->RedCircle) {  // Redcircle -> None
        this->setState(this->None);
    }
}

QPainterPath Chessman::shape() const {
    return ppshape;
}

QPoint Chessman::getPos() const {
    //std::cout << "x:" << pos.x() << " y:" << pos.y() << std::endl;
    return pos;
}

int Chessman::type() const {
    return 65535+233;
}
