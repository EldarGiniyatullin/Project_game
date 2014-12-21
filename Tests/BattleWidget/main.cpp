#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Personage *pers = new Personage();
	pers->setHP(1500);
	Personage *bot = new Personage;
	bot->setHP(500);

	Widget w(pers, bot);
	//w.show();

	return a.exec();
}
