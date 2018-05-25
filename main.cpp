#include "mainwindow.h"
//#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>

#include "./strategy/patternrecognizer.h"
void test() {

    PatternRecognizer przer("patterns.txt");

}

int main(int argc, char *argv[]) {

    //test();return 0;

    QApplication app(argc, argv);

    MainWindow qmw;

    qmw.setWindowTitle("23333333333");
    qmw.move((QApplication::desktop()->width()  - qmw.width())/2,
             (QApplication::desktop()->height() - qmw.height())/2);

    qmw.show();

    return app.exec();
}
