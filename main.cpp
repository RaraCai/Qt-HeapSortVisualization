//2252429蔡宇轩
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("HeapUp!");
    a.setApplicationDisplayName("HeapUp!");
    a.setWindowIcon(QIcon(":/icon/icon/app_icon.png"));

    MainWindow w;
    w.show();
    return a.exec();
}
