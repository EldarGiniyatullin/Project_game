#include "mapeditorwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MapEditorWidget w;
    w.show();

    return a.exec();
}
