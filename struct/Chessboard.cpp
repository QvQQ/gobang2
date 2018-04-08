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
#include <QMessageBox>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

#include <iostream>

Chessboard::Chessboard(QGraphicsView *gv, QLabel *label_black, QLabel *label_white, QLabel *label_round, QLabel *label_scoreOfCom, QLabel *label_scoreOfMan, QCheckBox *checkBox_blackReverse)
        : QGraphicsScene(gv), label_black(label_black), label_white(label_white), label_round(label_round), label_scoreOfCom(label_scoreOfCom), label_scoreOfMan(label_scoreOfMan), checkBox_blackReverse(checkBox_blackReverse) {

    int w = 32, h = 32;
    this->pm_back = new QPixmap(":/images/back");
    gv->setBackgroundBrush(pm_back->scaled(gv->width(), gv->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

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

    for (int i = 0; i < this->player.size; ++i) {
        QList<Chessman *> temp;
        for (int j = 0; j < this->player.size; ++j) {
            Chessman *gcm = new Chessman(QRect(i + 1, j + 1, w, h));
            gcm->setPos(26.5 + w*j - w/2.0, 26.5 + h*i - h/2.0);
            gcm->pm_step.setPos(26.5 + w*j - w/2.0, 26.5 + h*i - h/2.0);
            this->addItem(gcm);
            this->addItem(&gcm->pm_step);
            temp.append(gcm);
        }
        this->pmi_chessmen.append(temp);
    }

    this->connect(&this->player, &playchess::resultReady, this, &Chessboard::handleResult);
    //this->connect(&this->player, &playchess::finished, ...)
}

void Chessboard::handleResult(position rspos) {
    if (this->state != thinking) return;
    this->lastMan = this->pmi_chessmen[rspos.x - 1][rspos.y - 1];
    this->lastMan->setState(this->sideOfCom);
    this->lastMan->setStep(this->player.getRound());

    this->pmi_redcircle->setPos(this->lastMan->scenePos());
    this->pmi_redcircle->setZValue(233);
    this->updateScore();
    this->state = waiting;

    position pos; Direc direc;
    if (player.isDone(&direc, &pos)) {
        this->state = idling;
        finish(direc, pos);
    }
}

inline void Chessboard::updateRound() {
    this->label_round->setText(QString::number(this->player.getRound()));
}

inline void Chessboard::updateScore() {
    this->updateRound();
    this->label_black->setText(QString::number(this->player.curBlackScore));
    this->label_white->setText(QString::number(this->player.curWhiteScore));
}

void Chessboard::finish(Direc direc, position pos) {

    std::cout << ((this->lastMan->getState() == Chessman::Black) ? "Black" : "White") << " wins the game!"
              << " at (" << pos.x << ", " << pos.y << ")" << std::endl;

    this->checkBox_blackReverse->setEnabled(true);

    if (this->lastMan->getState() == Chessman::Black)
        this->label_black->setText("Winner!");
    else this->label_white->setText("Winner!");

    if (this->sideOfMan == this->lastMan->getState())
        this->label_scoreOfMan->setText(QString::number(++this->scoreOfMan));
    else this->label_scoreOfCom->setText(QString::number(++this->scoreOfCom));

    if (this->pmi_winLine != nullptr) {
        delete this->pmi_winLine;
        this->pmi_winLine = nullptr;
    }

    int w = 32;
    switch (direc) {
        case L:
            this->pmi_winLine = this->addLine(0, 0, w*5, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(0);
            this->pmi_winLine->setPos(pos.y * w - w/2 - w/4, pos.x * w - 6);
            break;
        case U:
            this->pmi_winLine = this->addLine(0, 0, w*5, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(90);
            this->pmi_winLine->setPos(pos.y * w + 1, pos.x * w - w/2);
            break;
        case LB:
            this->pmi_winLine = this->addLine(0, 0, w*7, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(-45);
            this->pmi_winLine->setPos(pos.y * w - w + w/8, pos.x * w + w/2 - w/8);
            break;
        case LU:
            this->pmi_winLine = this->addLine(0, 0, w*7, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(45);
            this->pmi_winLine->setPos(pos.y * w - w/2 - w/8 + 3, pos.x * w - w/2 - w/8);
            break;
    }

    this->pmi_winLine->setVisible(true);
    this->pmi_winLine->setZValue(233);

    return;
}

void Chessboard::restart() {
    if (this->state != idling) {
        if (QMessageBox::Cancel == QMessageBox::question((QWidget*)this->parent(), "Are you sure?", "Do you want to restart while playing?", QMessageBox::Cancel, QMessageBox::Ok))
            return;
        this->label_scoreOfCom->setText(QString::number(++this->scoreOfCom));
    }
    std::cout << "Restarted!" << std::endl;
    this->player.restart();
    this->checkBox_blackReverse->setEnabled(true);

    auto items = this->items();
    for (auto item : items) {
        if (item->type() == 65535 + 233) {
            auto man = dynamic_cast<Chessman *>(item);
            man->setState(Chessman::None);
        }
    }
    this->label_black->setText("0");
    this->label_white->setText("0");
    this->label_round->setText("0");

    this->pmi_redcircle->setPos(-20, -20);
    delete this->pmi_winLine;
    this->pmi_winLine = nullptr;
    this->lastMan = nullptr;
    this->state = waiting;
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
        if (this->checkBox_blackReverse->isEnabled()) this->checkBox_blackReverse->setEnabled(false);
        this->lastMan = dynamic_cast<Chessman *>(item);
        if (this->lastMan->getState() == Chessman::RedCircle) {
            this->state = thinking;
            this->lastMan->setState(this->sideOfMan);
            this->lastMan->setStep(this->player.getRound());
            position pos = {this->lastMan->getPos().x(), this->lastMan->getPos().y()};
            this->player.setChessman(pos, this->sideOfMan);
            this->updateScore();
            this->pmi_redcircle->setPos(this->lastMan->scenePos());
            this->pmi_redcircle->setZValue(233);

            position posa; Direc direc;
            if (player.isDone(&direc, &posa)) {
                this->state = idling;
                finish(direc, posa);
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
void Chessboard::searchDepthChanged(int index) {
    this->player.setSearchDepth(index + 1);
}
void Chessboard::displayStepsChanges(bool b) {
    for (auto &items : this->pmi_chessmen)
        for (auto &item : items) {
            item->setStepVisble(b);
        }
}
void Chessboard::blackReverseChanges(bool b) {
    if (b) {
        this->sideOfCom = Chessman::Black;
        this->sideOfMan = Chessman::White;
    } else {
        this->sideOfCom = Chessman::White;
        this->sideOfMan = Chessman::Black;
    }
}
