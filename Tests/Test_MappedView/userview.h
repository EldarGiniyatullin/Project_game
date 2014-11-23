#ifndef USERVIEW_H
#define USERVIEW_H

#include <QMainWindow>
#include "scenemanager.h"


namespace Ui {
class UserView;
}

class UserView : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserView(QWidget *parent = 0);
    ~UserView();
    SceneManager *scenka;

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::UserView *ui;
};

#endif // USERVIEW_H
