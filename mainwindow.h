#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "struct/Chessboard.h"

namespace Ui {
    class MainWindow233;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setScore(int score);

    void open();

private:
    Ui::MainWindow233 *ui;

    Chessboard *chessboard;
    QGraphicsView *gv;
};

#endif // MAINWINDOW_H
