#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Topic 1: ShapeButton (mainwindow.ui içinde)
    MainWindow w;
    w.show();

    return a.exec();
}
