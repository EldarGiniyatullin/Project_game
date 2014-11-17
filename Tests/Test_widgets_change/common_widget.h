#pragma once

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include "create_game_widget.h"
#include "main_menu_widget.h"

namespace Ui {
class Window;
}

class Common_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Common_widget(QWidget *parent = 0);
    ~Common_widget();
    QWidget *widgya;
    QWidget *mainMenuWidget;
    QWidget *createGameWidget;

public slots:
    void toCreateGame()
    {
            mainMenuWidget->hide();
            createGameWidget->showFullScreen();
    }
    void toMainMenu()
    {
        createGameWidget->hide();
        mainMenuWidget->showFullScreen();
    }

private:
    Ui::Window *ui;
};

