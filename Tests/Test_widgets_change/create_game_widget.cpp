#include "create_game_widget.h"
#include <QPixmap>
#include <QBitmap>

CreateNewGameWidget::CreateNewGameWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(this->parentWidget()->width(), this->parentWidget()->height());
    main_menu_button = new QPushButton(this);
    QPixmap pixmap2("://Images/Main_menu_button.png");
    main_menu_button->resize(pixmap2.size());
    main_menu_button->setIcon(pixmap2);
    main_menu_button->setMask(pixmap2.mask());
    main_menu_button->setIconSize(pixmap2.size());
    main_menu_button->move((this->width() - main_menu_button->width()) / 2, (this->height() - main_menu_button->width()) / 2);
    connect(main_menu_button, SIGNAL(clicked()), this, SLOT(mainMenuButtonClicked()));
}
