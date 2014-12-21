#include "widget.h"
#include "ui_widget.h"

void delay()
{
	QTime dieTime= QTime::currentTime().addSecs(1);

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

	srand (time(NULL));

	show();

	connect(this, SIGNAL(showed(Personage *, Personage *)), this, SLOT(battle(Personage *, Personage *)));

	emit showed(player, bot);
	delay();
}

void Widget::battle(Personage *player, Personage *bot)
{
	QGridLayout *layout = new QGridLayout();

	QLabel *playerText = new QLabel("Atacker");
	layout->addWidget(playerText, 0, 0);

	QGridLayout *playerLayout = new QGridLayout();
	QProgressBar *playerHP = new QProgressBar();
	playerHP->setMaximum(player->getHP());
	playerHP->setValue(player->getHP());
	QLabel *playerDamage = new QLabel("");
	playerLayout->addWidget(playerHP, 0, 0);
	playerLayout->addWidget(playerDamage, 0, 1);
	layout->addLayout(playerLayout, 0, 1);

	QLabel *botText = new QLabel("Defender");
	layout->addWidget(botText, 1, 0);

	QGridLayout *botLayout = new QGridLayout();
	QProgressBar *botHP = new QProgressBar();
	botHP->setMaximum(bot->getHP());
	botHP->setValue(bot->getHP());
	QLabel *botDamage = new QLabel("");
	botLayout->addWidget(botHP, 0, 0);
	botLayout->addWidget(botDamage, 0, 1);
	layout->addLayout(botLayout, 1, 1);

	playerHP->setFormat("%v");
	botHP->setFormat("%v");

	this->setLayout(layout);

	delay();

	while (bot->getHP() > 0 && player->getHP() > 0)
	{
		int random = rand() % 100 + 1;

		botDamage->setText(QString::number( (-1)*random));
		bot->setHP(bot->getHP() - random);
		botHP->setValue(bot->getHP());

		if (bot->getHP() < 0)
		{
			botHP->setValue(0);
			break;
		}

		delay();

		int random2 = rand() % 100 + 1;

		playerDamage->setText(QString::number((-1)*random2));
		player->setHP(player->getHP() - random2);
		playerHP->setValue(player->getHP());

		if (player->getHP() < 0)
		{
			playerHP->setValue(0);
			break;
		}

		delay();
	}
	delay();
}

Widget::~Widget()
{
	delete ui;
}
