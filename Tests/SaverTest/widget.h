#include <QWidget>
#include "saver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	Saver saver;

private:
	Ui::Widget *ui;
};
