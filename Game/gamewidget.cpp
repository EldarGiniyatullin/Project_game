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
    connect(this, SIGNAL(endedMove()), this, SLOT(nextMove()));

}

void GameWidget::winner(Fraction frac)
{
	if (frac == BLUE)
		QMessageBox::information(this, "Blue wins", "Now you can create another map or load one");
	else
		QMessageBox::information(this, "Red wins", "Now you can create another map or load one");
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
        if (pers && pers->currentPos() == settedPersonage->currentPos())
		{
			deletePersonage(fight(settedPersonage, pers));
		}
	}
	buttonsLayout->setEnabled(false);
}

Personage *GameWidget::fight(Personage *pers1, Personage *pers2)
{
	Widget w;
	w.Player = pers1;
	w.Bot = pers2;
	w.start();
	w.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	w.setModal(true);
	w.show();
	w.exec();

	while(w.isHidden() == false)
	{

	}

	if (pers1->getHP() <= 0)
		return pers1;
	else return pers2;
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
	if (numberOfBLues() == 0 || numberOfReds() == 0)
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
            if ((*bot)->currentPos() == (*enemy)->currentPos())
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

	Fraction temp;
	if (numberOfBLues() == 0)
	{
		temp = RED;
		emit winnerIs(temp);
	}

	if (numberOfReds() == 0)
	{
		temp = BLUE;
		emit winnerIs(temp);
	}
}

PlayerIs GameWidget::getPlayerIs(Fraction frac)
{
	return (frac == RED ? redPlayer : bluePlayer);
}

void GameWidget::nextMove()
{
//	if (numberOfBLues() != 0)
//	{
		currentFractionsMove = (currentFractionsMove == RED ? BLUE : RED);
        for (int i = 0; i < gameMap->listOfPersonages.size(); i++)
        {
            if (gameMap->listOfPersonages[i]->getPersFraction() == currentFractionsMove)
                gameMap->listOfPersonages[i]->updateSteps();
        }
		if (getPlayerIs(currentFractionsMove) == COMPUTER)
		{
			gameMap->setEnabled(false);
			buttonsLayout->setEnabled(false);
			playBot(currentFractionsMove);

			gameMap->setEnabled(true);
			buttonsLayout->setEnabled(true);
            emit endedMove();
        }
//	}

//	currentFractionsMove = RED;
}

void attackEnemy(Personage *pers)
{
	//    for (int i = 0; i < )
}
