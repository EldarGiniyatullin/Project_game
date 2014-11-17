#include "main_menu_widget.h"
#include <QPixmap>
#include <QBitmap>

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(this->parentWidget()->width(), this->parentWidget()->height());
    new_game_button = new QPushButton(this);
    QPixmap pixmap("://Images/New_game_button.png");

    new_game_button->resize(pixmap.size());
    new_game_button->setIcon(pixmap);
    new_game_button->setMask(pixmap.mask());
    new_game_button->setIconSize(pixmap.size());
    new_game_button->move((this->width() - new_game_button->width()) / 2, (this->height() - new_game_button->width()) / 2);
    connect(new_game_button, SIGNAL(clicked()), this, SLOT(createGameButtonClicked()));
}

