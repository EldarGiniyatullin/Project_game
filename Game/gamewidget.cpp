#include "gamewidget.h"
#include <ctime>

GameWidget::GameWidget(QWidget *parent) :
	currentFractionsMove(RED),
	settedPersonage(nullptr),
	redPlayer(PLAYER),
	bluePlayer(COMPUTER),
	currentPlayer(redPlayer),
	QWidget(parent)
{
	srand(time(NULL));
	editorLayout = new QHBoxLayout(this);
	gameMap = nullptr;
	//    editorLayout->addWidget(editMap->getView());
	buttonsLayout = new QGridLayout(this);

	QWidget *palitre = new QWidget;
	palitre->setLayout(buttonsLayout);
	palitre->setFixedHeight(300);
	palitre->setFixedWidth(250);
	editorLayout->addWidget(palitre, 0, Qt::AlignRight | Qt::AlignTop);

	//editorLayout->setSizeConstraint(QLayout::SetMinimumSize);

	saveButton = new QPushButton("Save");
	buttonsLayout->addWidget(saveButton, 1, 0);
	loadButton = new QPushButton("Load");
	buttonsLayout->addWidget(loadButton, 1, 1);
	moveButton = new QPushButton("Move");
	buttonsLayout->addWidget(moveButton, 2, 0);
	loadMap();

	connect(loadButton, SIGNAL(clicked()), this, SLOT(loadMap()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveMap()));
	connect(moveButton, SIGNAL(clicked()), this, SLOT(nextMove()));
	connect(this, SIGNAL(winnerIs(Fraction)), this, SLOT(winner(Fraction)));

}

void GameWidget::winner(Fraction frac)
{

}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
	if (this->gameMap->getView()->underMouse())
	{
		if (event->button() == Qt::LeftButton)
		{
			if (Personage *pers = gameMap->personageAt(gameMap->globalToMapCoordinates(event->pos())))
			{
				if (pers->getPersFraction() == currentFractionsMove)
				{
					if (settedPersonage)
					{
						gameMap->hidePersWay(settedPersonage);
					}
					settedPersonage = pers;
					gameMap->drawPersWay(pers);
				}
				else
				{
					if (settedPersonage)
					{
						gameMap->hidePersWay(settedPersonage);
					}
				}
			}
		}
		if (event->button() == Qt::RightButton)
		{
			if (settedPersonage)
			{
				gameMap->buildWay(settedPersonage, gameMap->globalToMapCoordinates(event->pos()));
				gameMap->drawPersWay(settedPersonage);
			}
		}
	}
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
	buttonsLayout->setEnabled(false);
	Personage *pers = nullptr;
	if (event->key() == Qt::Key_Space && (currentPlayer == PLAYER) && settedPersonage)
	{
		if (settedPersonage->getWayToGo().size() != 0 && gameMap->personageAt(settedPersonage->getWayToGo().last())
				&& gameMap->personageAt(settedPersonage->getWayToGo().last())->getPersFraction() != settedPersonage->getPersFraction())
			pers = gameMap->personageAt(settedPersonage->getWayToGo().last());
		gameMap->movePersonage(settedPersonage);
		if (pers)
		{
			deletePersonage(fight(settedPersonage, pers));
		}
	}
	buttonsLayout->setEnabled(false);
}

Personage *GameWidget::fight(Personage *pers1, Personage *pers2)
{
	Widget w(pers1, pers2);
	w.show();
	if (pers1->getHP() <= 0)
		return pers1;
	else return pers2;
	//    Personage *bluePers = (pers1->getPersFraction() == BLUE ? pers1 : pers2);
	//return (rand() % 2 == 0 ? pers1 : pers2);
}

int GameWidget::numberOfReds()
{
	int result = 0;
	QList<Personage*>::Iterator i = this->gameMap->listOfPersonages.begin();
	for (i; i != this->gameMap->listOfPersonages.end(); ++i)
	{
		if ((*i)->getPersFraction() == RED)
			result++;
	}

	return result;
}

int GameWidget::numberOfBLues()
{
	int result = 0;
	QList<Personage*>::Iterator i = this->gameMap->listOfPersonages.begin();
	for (; i != this->gameMap->listOfPersonages.end(); ++i)
	{
		if ((*i)->getPersFraction() == BLUE)
			result++;
	}

	return result;
}

void GameWidget::playBot(Fraction frac)
{
	if (numberOfBLues() == 0 || numberOfReds() == BLUE)
		return;

	Personage *loser = nullptr;

	QList<Personage*>::Iterator bot = this->gameMap->listOfPersonages.begin();
	for (bot; bot != this->gameMap->listOfPersonages.end(); ++bot)
	{
		if ((*bot)->getPersFraction() == frac)
			break;
	}

	QList<Personage*>::Iterator enemy = this->gameMap->listOfPersonages.begin();
	for (enemy; enemy != this->gameMap->listOfPersonages.end(); ++enemy)
	{
		if ((*enemy)->getPersFraction() != frac)
			break;
	}

	if ((*bot)->getPersFraction() != frac)
		return;
	if ((*enemy)->getPersFraction() == frac)
		return;

	while (numberOfBLues() > 0 && numberOfReds() > 0 && (*bot) != nullptr && (*enemy) != nullptr && (*enemy)->getPersFraction() != frac && (*bot)->getPersFraction() == frac)
	{
		gameMap->buildWay((*bot), QPoint((*enemy)->getXCoord(), (*enemy)->getYCoord()));

		if ((*bot)->getWayToGo().size() != 0)
		{
			gameMap->movePersonage((*bot));
			loser = fight(*bot, *enemy);
		}
		else
		{
			if ((*enemy) == this->gameMap->listOfPersonages.last())
				return;

			QList<Personage*>::Iterator tempEnemy = this->gameMap->listOfPersonages.begin();
			for (tempEnemy; tempEnemy != this->gameMap->listOfPersonages.end(); ++tempEnemy)
			{
				if ((*enemy)->getPersFraction() != frac && enemy !=tempEnemy)
					break;
			}

			if ((*tempEnemy)->getPersFraction() == frac || tempEnemy == enemy)
				return;
			else
				enemy = tempEnemy;

			continue;
		}

		if (loser == (*bot) && loser == this->gameMap->listOfPersonages.last())
		{
			deletePersonage(loser);
			return;
		}

		if ((*bot) == this->gameMap->listOfPersonages.last())
		{
			deletePersonage(loser);
			return;
		}

		if (loser == (*bot) && numberOfBLues() == 1)
		{
			{
				deletePersonage(loser);
				return;
			}
		}

		if (loser == (*enemy) && numberOfReds() == 1)
		{
			{
				deletePersonage(loser);
				return;
			}
		}

		++bot;
		for (bot; bot != this->gameMap->listOfPersonages.end(); ++bot)
		{
			if ((*bot)->getPersFraction() == frac && ((*bot) != loser))
				break;
		}

		if (((*bot)->getPersFraction() != frac) || ((*bot) == loser))
		{
			deletePersonage(loser);
			return;
		}

		if (loser == (*enemy))
		{
			deletePersonage(loser);
			for (enemy = this->gameMap->listOfPersonages.begin(); enemy != this->gameMap->listOfPersonages.end(); ++enemy)
			{
				if (((*enemy)->getPersFraction() != frac))
					break;
			}

			if ((*enemy)->getPersFraction() == frac)
				return;

			continue;
		}

		deletePersonage(loser);
	}
}

void GameWidget::deletePersonage(Personage *pers)
{
	if (settedPersonage == pers)
		settedPersonage = nullptr;
	gameMap->deletePersonage(pers);
}

PlayerIs GameWidget::getPlayerIs(Fraction frac)
{
	return (frac == RED ? redPlayer : bluePlayer);
}

void GameWidget::nextMove()
{
	if (numberOfBLues() != 0)
	{
		currentFractionsMove = (currentFractionsMove == RED ? BLUE : RED);
		if (getPlayerIs(currentFractionsMove) == COMPUTER)
		{
			gameMap->setEnabled(false);
			buttonsLayout->setEnabled(false);
			playBot(currentFractionsMove);

			gameMap->setEnabled(true);
			buttonsLayout->setEnabled(true);
		}
	}

	currentFractionsMove = RED;
}

void attackEnemy(Personage *pers)
{
	//    for (int i = 0; i < )
}
