#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QPainter>

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

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addEllipse(23, 23, 100, 100, QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
    this->ui->graphicsView->setScene(scene);

    //this->ui->horizontalLayoutWidget->setVisible(false);

    this->ui->pushButton->setText("draw");
    this->ui->pushButton_2->setText("clear");

    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, [this](){
        this->path->addEllipse(this->width()/2, this->height()/2, this->width()/4, this->height()/4);
    });
    QObject::connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this](){
        delete this->path;
        this->path = new QPainterPath();
    });

    this->path = new QPainterPath();
    // this->ui->graphicsView->re

    statusBar();
}

void MainWindow::open() {
    QMessageBox::information(this, "23333", "Talk is cheap, show me the code.");
}

void MainWindow::paintEvent(QPaintEvent *event) {

    QMainWindow::paintEvent(event);
    QPainter painter(this);

    //painter.setWindow(0, 0, this->width()/2, this->height()/2);
    painter.setViewport(this->width()/2, this->height()/2, this->width()/2, this->height()/2);

    painter.drawLine(0, this->height()/2, this->width(), this->height()/2);
    painter.drawText(QRect(this->width()/4, this->height()/4, this->width()/2, this->height()/2), "233333");
    painter.setPen(Qt::red);
    painter.setBrush(QColor(255, 100, 20));
    painter.drawRect(this->width()/8, this->height()/8, this->width()/4, this->height()/4);

    painter.setPen(QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(0, this->height()/3, this->width()/2, this->height()/3);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(300, 150, 200, 150);

     QPainter *p = new QPainter(this);
     p->setPen(QPen(Qt::black, 5, Qt::DashDotDotLine, Qt::RoundCap));
     p->setBrush(Qt::red);
     p->drawPath(*this->path);
     delete p;
}

MainWindow::~MainWindow()
{
    delete ui;
}
