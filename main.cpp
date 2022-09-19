#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.show();

    return app.exec();
}
