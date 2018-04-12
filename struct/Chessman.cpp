#include "Chessman.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
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
    this->setStepVisble(true);
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

void Chessman::setStep(int step) {
    this->stepCount = step;

    QPixmap pim(this->pm.none.width(), this->pm.none.height());
    pim.fill(Qt::transparent);
    QPainter pter(&pim);
    if (this->getState() == Black) {
        pter.setPen(QPen(Qt::white, 2));
        pter.setBrush(Qt::white);
    } else if (this->getState() == White) {
        pter.setPen(QPen(Qt::black, 2));
        pter.setBrush(Qt::black);
    }
    pter.drawText(this->pm.none.rect(), QString::number(step), QTextOption(Qt::AlignCenter));
    this->pm_stepIndicate.setPixmap(pim);
}

void Chessman::clearStep() {
    this->stepCount = 0;
    QPixmap pim(this->pm.none.width(), this->pm.none.height());
    pim.fill(Qt::transparent);
    this->pm_stepIndicate.setPixmap(pim);
}

void Chessman::setStepVisble(bool b) {
    this->pm_stepIndicate.setVisible(b);
    this->pm_stepIndicate.setZValue(2333);
}

QGraphicsItem *Chessman::getStepItem() {
    return &this->pm_stepIndicate;
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
    return pos;
}

int Chessman::type() const {
    return 65535+233;
}
