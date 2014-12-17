#pragma once

#include <QWidget>

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

public slots:
	void changeTypeToProps();
	void changeTypeToSurf();
	void changeTypeToStuff();

private:
	Ui::Widget *ui;

	LayoutType type;
};
