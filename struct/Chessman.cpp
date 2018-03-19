#include "Chessman.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QPainterPath>
#include <iostream>

Chessman::Chessman(int w, int h) : state(this->None){

    this->setAcceptHoverEvents(true);
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    /////////////// pm.none
    this->pm.none = QPixmap(w, h);
    this->pm.none.fill(Qt::transparent);

    /////////////// pm.redcircle
    this->pm.redcircle = QPixmap(w, h);
    this->pm.redcircle.fill(Qt::transparent);

    QPainter pter(&this->pm.redcircle);
    pter.setPen(QPen(Qt::black, 2));
    pter.setBrush(Qt::red);
    pter.fillRect(this->pm.redcircle.rect(), Qt::transparent);
    pter.setRenderHint(QPainter::Antialiasing);
    pter.drawEllipse(w/3, h/3, w/3, h/3);

    /////////////// pm.black
    this->pm.black = QPixmap(":/images/black");
    this->pm.black = this->pm.black.scaled(w*0.9, h*0.9, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->ppshape.addEllipse(this->pm.black.rect());

    /////////////// pm.white
    this->pm.white = QPixmap(":/images/white");
    this->pm.white = this->pm.white.scaled(w*0.9, h*0.9, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    /////////////// set default
    this->setPixmap(this->pm.none);
}

Chessman::~Chessman() {
    ;
}

void Chessman::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    std::cout << "enter:" << event->pos().x() << ", " << event->pos().y() << std::endl;

    if (this->state == this->None) {  // None -> Redcircle
        this->setPixmap(this->pm.redcircle);
        this->state = this->Redcircle;
    }
}

void Chessman::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    std::cout << "leave:" << event->pos().x() << ", " << event->pos().y() << std::endl;

    if (this->state == this->Redcircle) {
        this->setPixmap(this->pm.none);
        this->state = this->None;
    }
}

void Chessman::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    std::cout << "press:" << event->pos().x() << ", " << event->pos().y() << std::endl;

    if (this->state == this->Redcircle) {
        this->setPixmap(this->pm.black);
        this->state = this->Black;
        this->setAcceptHoverEvents(false);
        this->setAcceptedMouseButtons(0);
    }
}

QPainterPath Chessman::shape() const {
    return ppshape;
}
