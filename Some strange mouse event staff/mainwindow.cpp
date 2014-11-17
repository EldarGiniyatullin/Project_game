#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <QDebug>
#include <QMouseEvent>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	int i = 0;
	while (i < ui->centralWidget->children().length())
	{
		//connect(ui->centralWidget->children()[i], SIGNAL(QMouseEvent::QEvent), this, SLOT(showJbjectName(QMouseEvent *)));
		i++;
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showJbjectName(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		/*qDebug() << QCursor :: pos();
		qDebug() << QApplication::widgetAt(event->pos())->objectName();*/
	}

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	emit MainWindow::leftcla(event);

	if (event->button() == Qt::LeftButton)
	{
		qDebug() << QCursor :: pos();
		qDebug() << QApplication::widgetAt(QCursor :: pos())->objectName();
	}
}
