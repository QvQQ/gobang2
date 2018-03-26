#include "Chessboard.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEngine>
#include <QList>
#include <QLabel>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

#include <iostream>

Chessboard::Chessboard(QGraphicsView *gv, QLabel *label) : QGraphicsScene(gv), scoreLabel(label) {
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
    ///////////
    this->connect(&this->player, &playchess::resultReady, this, &Chessboard::handleResult);
    //this->connect(&this->player, &playchess::finished, ...)
}

void Chessboard::handleResult(position rspos) {
    this->lastMan = this->pmi_chessmen[rspos.x - 1][rspos.y - 1];
    this->lastMan->setState(static_cast<Chessman::State>(-this->lastVal));

    this->pmi_redcircle->setPos(this->lastMan->scenePos());
    this->pmi_redcircle->setZValue(233);
    this->updateScore();
    this->state = waiting;

    int val = player.isDone(rspos);
    if (val) {
        this->state = idling;
        finish(val);
    }
}

void Chessboard::updateScore() {
    QString score;
    score.append("Black:");
    score.append(QString::number(this->player.curBlackScore));
    score.append("\n");
    score.append("White:");
    score.append(QString::number(this->player.curWhiteScore));
    this->scoreLabel->setText(score);
}

void Chessboard::finish(int val) {

    std::cout << ((val == 1) ? "Black" : "White") << " wins the game!" << std::endl;
    this->scoreLabel->setText(((val == 1) ? "Black wins!" : "White wins!"));

    return;
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
            position pos = {this->lastMan->getPos().x(), this->lastMan->getPos().y()};
            this->player.setChessman(pos, this->lastVal);
            this->updateScore();
            this->pmi_redcircle->setPos(this->lastMan->scenePos());
            this->pmi_redcircle->setZValue(233);

            int val = player.isDone(pos);
            if (val) {
                this->state = idling;
                this->finish(val);
            } else {
                // start a new thread and solve
                if (this->player.isFinished() || !this->player.isRunning()) {
                    player.start();
                }
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}
