#include "mapfacade.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapFacade w(40, 140, 29);
    w.show();

    return a.exec();
}
