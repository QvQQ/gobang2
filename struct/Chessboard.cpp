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
#include <QLCDNumber>
#include <QMessageBox>
#include "struct/Chessman.h"
#include "strategy/playchess.h"

#include <iostream>

Chessboard::Chessboard(QGraphicsView *gv, QLabel *label_black, QLabel *label_white, QLCDNumber *lcdNumber_round, QLabel *label_scoreOfCom, QLabel *label_scoreOfMan, QCheckBox *checkBox_blackReverse, QPushButton *button_regret)
        : QGraphicsScene(gv), label_black(label_black), label_white(label_white), lcdNumber_round(lcdNumber_round), label_scoreOfCom(label_scoreOfCom), label_scoreOfMan(label_scoreOfMan), checkBox_blackReverse(checkBox_blackReverse), button_regret(button_regret) {

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
            gcm->pm_stepIndicate.setPos(25 + w*j - w/2.0, 24.5 + h*i - h/2.0);
            this->addItem(gcm);
            this->addItem(&gcm->pm_stepIndicate);
            temp.append(gcm);
        }
        this->pmi_chessmen.append(temp);
    }

    this->connect(&this->player, &playchess::resultReady, this, &Chessboard::handleResult);
    //this->connect(&this->player, &playchess::finished, ...)
}

inline void Chessboard::updateRound() {
    this->lcdNumber_round->display(this->player.getRound());
}

inline void Chessboard::updateScore() {
    this->updateRound();
    this->label_black->setText(QString::number(this->player.curBlackScore));
    this->label_white->setText(QString::number(this->player.curWhiteScore));
}

void Chessboard::finish(Direc direc, Position pos) {

    std::cout << ((this->lastMan->getState() == Chessman::Black) ? "Black" : "White") << " wins the game!"
              << " at (" << pos.first << ", " << pos.second << ")" << std::endl;

    this->checkBox_blackReverse->setEnabled(true);
    this->button_regret->setEnabled(false);

    if (this->lastMan->getState() == Chessman::Black)
        this->label_black->setText("Winner!");
    else this->label_white->setText("Winner!");

    if (this->lastMan->getState() == this->sideOfMan)
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
            this->pmi_winLine->setPos(pos.second * w - w/2 - w/4, pos.first * w - 6);
            break;
        case U:
            this->pmi_winLine = this->addLine(0, 0, w*5, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(90);
            this->pmi_winLine->setPos(pos.second * w + 1, pos.first * w - w/2);
            break;
        case LB:
            this->pmi_winLine = this->addLine(0, 0, w*7, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(-45);
            this->pmi_winLine->setPos(pos.second * w - w + w/8, pos.first * w + w/2 - w/8);
            break;
        case LU:
            this->pmi_winLine = this->addLine(0, 0, w*7, 0, QPen(QBrush(Qt::red), w/6));
            this->pmi_winLine->setTransformOriginPoint(0, -w/4);
            this->pmi_winLine->setRotation(45);
            this->pmi_winLine->setPos(pos.second * w - w/2 - w/8 + 3, pos.first * w - w/2 - w/8);
            break;
    }

    this->pmi_winLine->setVisible(true);
    this->pmi_winLine->setZValue(2334);

    return;
}

void Chessboard::regret() {
    stu_stepState com = this->stepState.back();
    this->stepState.pop_back();
    stu_stepState man = this->stepState.back();
    this->stepState.pop_back();

    if (this->stepState.empty())
        this->button_regret->setEnabled(false);

    this->player.regret({com.curMan->getPos().x(), com.curMan->getPos().y()});
    this->player.regret({man.curMan->getPos().x(), man.curMan->getPos().y()});
    com.curMan->clearStep();
    man.curMan->clearStep();
    com.curMan->setState(Chessman::None);
    man.curMan->setState(Chessman::None);
    this->updateScore();

    if (this->stepState.empty()) {
        this->pmi_redcircle->setPos(-20, -20);
    } else {
        man.lastMan->clearStep();
        this->pmi_redcircle->setPos(man.lastMan->scenePos());
        this->pmi_redcircle->setZValue(233);
    }
    this->lastMan = man.lastMan;
}

void Chessboard::restart() {
    if (this->playState != idling) {
        if (QMessageBox::Cancel == QMessageBox::question((QWidget*)this->parent(), "Are you sure?", "Do you want to restart while playing?", QMessageBox::Cancel, QMessageBox::Ok))
            return;
        this->label_scoreOfCom->setText(QString::number(++this->scoreOfCom));
    }
    std::cout << "Restarted!" << std::endl;
    this->player.restart();

    for (auto &item : this->items()) {
        if (item->type() == 65535 + 233) {
            auto man = dynamic_cast<Chessman *>(item);
            man->setState(Chessman::None);
            man->clearStep();
        }
    }
    this->label_black->setText("0");
    this->label_white->setText("0");
    this->lcdNumber_round->display(0);

    this->pmi_redcircle->setPos(-20, -20);
    delete this->pmi_winLine;
    this->pmi_winLine = nullptr;
    this->lastMan = nullptr;
    this->playState = waiting;
    if (this->checkBox_blackReverse->isChecked()) {
        this->playState = thinking;
        this->player.setChessman({8, 8});
        this->handleResult({8, 8});
    }
    this->stepState.clear();
    this->button_regret->setEnabled(false);
}

Chessboard::~Chessboard() {
    delete this->pm_back;
    for (auto &pmi : this->pmi_chessmen)
        for (auto &pmii : pmi)
            delete pmii;
}

void Chessboard::handleResult(Position rspos) {
    if (this->playState != thinking) return;
    Chessman *curMan = this->pmi_chessmen[rspos.first - 1][rspos.second - 1];

    this->playState = waiting;
    this->stepState.push_back({curMan, this->lastMan});

    if (this->lastMan)
        this->lastMan->setStep(this->player.getRound() - 1);

    curMan->setState(this->sideOfCom);
    this->updateScore();

    this->pmi_redcircle->setPos(curMan->scenePos());
    this->pmi_redcircle->setZValue(233);
    this->lastMan = curMan;

    this->button_regret->setEnabled(true);

    Position pos; Direc direc;
    if (player.isDone(&direc, &pos)) {
        this->playState = idling;
        finish(direc, pos);
    }
}

void Chessboard::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item = this->itemAt(event->scenePos(), QTransform());

    if (this->playState == waiting && item && item->type() == 65535 + 233) {
        Chessman *curMan = dynamic_cast<Chessman *>(item);
        if (curMan->getState() == Chessman::RedCircle) {
            this->playState = thinking;
            this->stepState.push_back({curMan, this->lastMan});

            curMan->setState(this->sideOfMan);
            Position pos = {curMan->getPos().x(), curMan->getPos().y()};
            this->player.setChessman(pos, this->sideOfMan);
            this->updateScore();

            this->pmi_redcircle->setPos(curMan->scenePos());
            this->pmi_redcircle->setZValue(233);
            if (this->lastMan)
                this->lastMan->setStep(this->player.getRound() - 1);
            this->lastMan = curMan;

            this->button_regret->setEnabled(false);

            Position posa; Direc direc;
            if (player.isDone(&direc, &posa)) {
                this->playState = idling;
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
    bool flag = false;
    if (this->playState != idling) {
        if (QMessageBox::Ok == QMessageBox::question((QWidget*)this->parent(), "Are you sure?", "Do you want to restart while playing?", QMessageBox::Cancel, QMessageBox::Ok)) {
            this->label_scoreOfCom->setText(QString::number(++this->scoreOfCom));
            flag = true;
        } else {
            this->checkBox_blackReverse->setChecked(!b);
            return;
        }
    }
    if (b) {
        this->sideOfCom = Chessman::Black;
        this->sideOfMan = Chessman::White;
    } else {
        this->sideOfCom = Chessman::White;
        this->sideOfMan = Chessman::Black;
    }
    if (flag) {
        this->playState = idling;
        this->restart();
    }
}
