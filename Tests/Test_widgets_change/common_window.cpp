#include "common_widget.h"
#include "ui_window.h"

Common_widget::Common_widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    this->resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    mainMenuWidget = new MainMenuWidget(this);
    createGameWidget = new CreateNewGameWidget(this);

    mainMenuWidget->showFullScreen();
    createGameWidget->hide();
    connect(createGameWidget, SIGNAL(toMainMenuSignal()), this, SLOT(toMainMenu()));
    connect(mainMenuWidget, SIGNAL(toCreateGameSignal()), this, SLOT(toCreateGame()));
}

Common_widget::~Common_widget()
{
    delete ui;
}

//void Window::changeWidget2(QWidget *widget)
//{
//    delete widgya;
//    widgya = widget;
//}
