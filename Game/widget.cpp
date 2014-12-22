#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QDialog *parent) :
	QDialog(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	QGridLayout *layout = new QGridLayout();

	QLabel *playerText = new QLabel("Atacker");
	layout->addWidget(playerText, 0, 0);

	QGridLayout *playerLayout = new QGridLayout();
	playerHP = new QProgressBar();

	playerDamage = new QLabel("");
	playerLayout->addWidget(playerHP, 0, 0);
	playerLayout->addWidget(playerDamage, 0, 1);
	layout->addLayout(playerLayout, 0, 1);

	QLabel *botText = new QLabel("Defender");
	layout->addWidget(botText, 1, 0);

	QGridLayout *botLayout = new QGridLayout();
	botHP = new QProgressBar();

	botDamage = new QLabel("");
	botLayout->addWidget(botHP, 0, 0);
	botLayout->addWidget(botDamage, 0, 1);
	layout->addLayout(botLayout, 1, 1);


	this->setLayout(layout);

	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(battle()));
}

void Widget::start()
{
	playerHP->setMaximum(Player->getHP());
	playerHP->setValue(Player->getHP());

	turn = Player->getPersFraction();
	botHP->setMaximum(Bot->getHP());
	botHP->setValue(Bot->getHP());

	playerHP->setFormat("%v");
	botHP->setFormat("%v");

	timer->start(200);
}

void Widget::battle()
{
	if (turn == Player->getPersFraction())
	{
		int random = rand() % 100 + 1;
		botDamage->setText(QString::number( (-1)*random));
		Bot->setHP(Bot->getHP() - random);
		botHP->setValue(Bot->getHP());

		if (Bot->getHP() < 0)
		{
			botHP->setValue(0);
			turn = BLACK;
			timer->setInterval(1000);

			return;
		}

		turn = Bot->getPersFraction();

		return;
	}

	if (turn == Bot->getPersFraction())
	{
		int random2 = rand() % 100 + 1;

		playerDamage->setText(QString::number((-1) * random2));
		Player->setHP(Player->getHP() - random2);
		playerHP->setValue(Player->getHP());

		if (Player->getHP() < 0)
		{
			playerHP->setValue(0);
			turn = BLACK;
			timer->setInterval(1000);

			return;
		}

		turn = Player->getPersFraction();

		return;
	}

	if (turn = BLACK)
	{
		timer->stop();
		this->hide();
	}
}

Widget::~Widget()
{
	delete ui;
}
