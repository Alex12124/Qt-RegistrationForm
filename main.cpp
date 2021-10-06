#include <QApplication>
#include "authwindow.h"
#include "regwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.Display();
    return a.exec();
}
