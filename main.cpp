#include "forms/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//自动进行高DPI缩放
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
