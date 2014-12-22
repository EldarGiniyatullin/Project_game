#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QTextEdit>
#include <QString>
#include <QLabel>
#include <QTime>
#include <time.h>
#include <QProgressBar>
#include <QMessageBox>
#include <QTimer>
#include <QDialog>

#include "personage.h"

namespace Ui {
class Widget;
}

class Widget : public QDialog
{
	Q_OBJECT

public:
	explicit Widget(QDialog *parent = 0);
	~Widget();
	void start();
	Personage *Player;
	Personage *Bot;
	Fraction turn;

public slots:
	void battle();

private:
	Ui::Widget *ui;
	QTimer *timer;
	QProgressBar *playerHP;
	QLabel *playerDamage;
	QLabel *botDamage;
	QProgressBar *botHP;

};
