#include "mainwindow.h"
#include <QApplication>
#include "mainui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/myappico.ico"));
    mainUI ll;
    ll.show();
    return a.exec();
}
