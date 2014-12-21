#include "widget.h"
#include "ui_widget.h"

void delay()
{
	QTime dieTime= QTime::currentTime().addSecs(3);

	while(QTime::currentTime() < dieTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

Widget::Widget(Personage *player, Personage *bot, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);



	connect(this, SIGNAL(showed(Personage *, Personage *)), this, SLOT(battle(Personage *, Personage *)));

	emit showed(player, bot);
}

void Widget::battle(Personage *player, Personage *bot)
{
	QGridLayout *layout = new QGridLayout();

	this->setLayout(layout);
	QTextEdit *playerText = new QTextEdit("Player\n" +  QString::number(player->getHP()));
	QTextEdit *botText = new QTextEdit("Bot\n" + QString::number(bot->getHP()));

	QLabel *playerDamage = new QLabel("");
	QLabel *botDamage = new QLabel("");

	layout->addWidget(playerText, 0, 0);
	layout->addWidget(botText, 1, 0);
	layout->addWidget(playerDamage, 0, 1);
	layout->addWidget(botDamage, 1, 1);

	while(bot->getHP() > 0 && player->getHP() > 0)
	{
		int random = rand() % 100;
		playerDamage->setText(QString::number(random));
		bot->setHP(bot->getHP() - random);
		botText->setText("Bot\n" + QString::number(bot->getHP()));

		if (bot->getHP() < 0)
			break;

		this->show();

		delay();

		random = rand() % 100;
		botDamage->setText(QString::number(random));
		player->setHP(player->getHP() - random);
		playerText->setText("Player\n" + QString::number(bot->getHP()));

		if (player->getHP() < 0)
			break;

		this->show();

		delay();
	}
}

Widget::~Widget()
{
	delete ui;
}
