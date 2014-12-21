#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Personage *bla = new Personage();
	bla->setHP(1564);
	Personage *bla2 = new Personage;
	bla2->setHP(154);

	Widget w(bla, bla2);
	w.show();

	return a.exec();
}
