#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QTextEdit>
#include <QString>
#include <QLabel>
#include <QTime>
#include <time.h>
#include <QProgressBar>

#include "personage.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(Personage *player, Personage *bot, QWidget *parent = 0);
	~Widget();

signals:
	void showed(Personage *player, Personage *bot);

public slots:
	void battle(Personage *player, Personage *bot);

private:
	Ui::Widget *ui;

};
