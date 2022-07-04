#include "clientdatatransfer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientDataTransfer w;
    w.resize(600, 300);
    w.show();
    return a.exec();
}
