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
    //this->set;
    ///////////////
    this->pm.none = new QPixmap(w, h);
    this->pm.none->fill(Qt::transparent);
    ///////////////
    this->pm.redcircle = new QPixmap(w, h);
    this->pm.redcircle->fill(Qt::transparent);

    QPainter pter(this->pm.redcircle);
    pter.setPen(QPen(Qt::black, 2));
    pter.setBrush(Qt::red);
    pter.fillRect(this->pm.redcircle->rect(), Qt::transparent);
    pter.drawEllipse(w/3, h/3, w/3, h/3);
    ///////////////
    this->pm.black = new QPixmap(":/images/black");
    *this->pm.black = this->pm.black->scaled(w, h);
    this->pm.black->fill(Qt::transparent);
    this->ppshape.addEllipse(this->pm.black->rect());

//  this->pm.white = new QPixmap(w, h);
//  this->pm.white->fill(Qt::transparent);

    this->setPixmap(*this->pm.none);
}

Chessman::~Chessman() {
    ;
}

void Chessman::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    std::cout << "enter:" << event->pos().x() << ", " << event->pos().y() << std::endl;

    if (this->state == this->None) {  // None -> Redcircle
        this->setPixmap(*this->pm.redcircle);
        this->state = this->Redcircle;
    }
}

void Chessman::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    std::cout << "leave:" << event->pos().x() << ", " << event->pos().y() << std::endl;

    if (this->state == this->Redcircle) {
        this->setPixmap(*this->pm.none);
        this->state = this->None;
    }
}

void Chessman::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    std::cout << "press:" << event->pos().x() << ", " << event->pos().y() << std::endl;
}

QPainterPath Chessman::shape() const {
    return ppshape;
}
