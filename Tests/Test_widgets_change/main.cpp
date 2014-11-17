#include "common_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Common_widget w;
    w.showFullScreen();

    return a.exec();
}
