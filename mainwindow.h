#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow233;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void open();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow233 *ui;
    bool flag = false;
    QPainterPath *path;
};

#endif // MAINWINDOW_H
