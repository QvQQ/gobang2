#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QPainter>
#include "struct/Chessboard.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow233)
{
    ui->setupUi(this);

    QAction *action = new QAction("A^Action", this);
    action->setShortcut(QKeySequence::Save);
    action->setStatusTip("Hahahaha...");
    connect(action, &QAction::triggered, this, &MainWindow::open);

    QMenu *QAQ = menuBar()->addMenu("QAQ");
    QAQ->addAction(action);

    this->gv = this->ui->graphicsView;
    this->chessboard = new Chessboard(this->gv, this->ui->label_score_black, this->ui->label_score_white, this->ui->label_round, this->ui->label_scoreOfCom, this->ui->label_scoreOfMan, this->ui->checkBox_blackReverse);
    this->chessboard->addLine(-gv->width(), -gv->height(), gv->width(), gv->height());
    this->chessboard->setParent(this);

    this->gv->setScene(this->chessboard);
    this->gv->setSceneRect(0, 0, this->gv->width(), this->gv->height());

    QObject::connect(this->ui->button_restart, &QPushButton::clicked, this, [this]() {
        this->chessboard->restart();
    });
    QObject::connect(this->ui->comboBox_searchDepth, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){this->chessboard->searchDepthChanged(index);});
    QObject::connect(this->ui->checkBox_steps, &QCheckBox::stateChanged, this, [this](int state){this->chessboard->displayStepsChanges(state);});
    QObject::connect(this->ui->checkBox_blackReverse, &QCheckBox::stateChanged, this, [this](int state){this->chessboard->blackReverseChanges(state);});
}

void MainWindow::open() {
    QMessageBox::information(this, "23333", "Talk is cheap, show me the code.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
