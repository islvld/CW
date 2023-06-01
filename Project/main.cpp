#include "mainwindow.h"
#include <QApplication>
#include "auth.h"
#include "graphics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth w;
    w.show();
    return a.exec();
}
