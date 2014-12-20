#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>
#include  <QHBoxLayout>
#include <QPushButton>
#include "mapfacade.h"
#include "saverloader.h"

enum PlayerIs{PLAYER, COMPUTER};

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

    Fraction currentFractionsMove;
    MapFacade *gameMap;
    QHBoxLayout *editorLayout;
    QGridLayout *buttonsLayout;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *makeMove;
    Personage *settedPersonage;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    Personage *fight(Personage *pers1, Personage *pers2);
    PlayerIs redPlayer;
    PlayerIs blueplayer;
signals:

public slots:
    void saveMap()
    {
        MapFacadeSaveObject saveObj = gameMap->saveToObject();
        SaverLoader saver;
        saver.save(saveObj);
    }
    void loadMap()
    {
        SaverLoader loader;
        MapFacadeSaveObject saveObj = loader.load();
        if (gameMap)
            delete gameMap;
        gameMap = new MapFacade(saveObj, 29, this);
        this->gameMap->show();
        gameMap->getView()->show();
    }

};
