#pragma once

#include <QWidget>
#include <qpushbutton.h>

enum LayoutType {SURFACE = 0, PROPS, SOMESTUFF, NOTHING};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	LayoutType type;

public slots:
	void changeTypeToProps();
	void changeTypeToSurf();
	void changeTypeToStuff();


private:
	Ui::Widget *ui;
};
