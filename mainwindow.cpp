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

    this->ui->pushButton->setText("draw");
    this->ui->pushButton_2->setText("clear");
    ////////////////////////////

    this->gv = this->ui->graphicsView;
    this->chessboard = new Chessboard(15, this->gv);
    this->chessboard->addLine(-gv->width(), -gv->height(), gv->width(), gv->height());
    this->chessboard->addLine(0, 0, 20, 0);
    this->gv->setScene(this->chessboard);
    this->gv->setSceneRect(0, 0, this->gv->width(), this->gv->height());

    statusBar();
}

void MainWindow::open() {
    QMessageBox::information(this, "23333", "Talk is cheap, show me the code.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
