#include "mainwindow.h"
#include <QApplication>
struct process p[10],p1[10],temp;
std::queue<int>q1;
int nombre;
int ch;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.setWindowIcon(QIcon(":/pic/pic/pic.png"));
    w.setCursor(Qt::PointingHandCursor);
    w.setWindowTitle(QString::fromUtf8("simulation d'ordanance des processus"));
    w.show();

    return a.exec();
}
