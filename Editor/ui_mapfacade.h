/********************************************************************************
** Form generated from reading UI file 'mapfacade.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPFACADE_H
#define UI_MAPFACADE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapFacade
{
public:

    void setupUi(QWidget *MapFacade)
    {
        if (MapFacade->objectName().isEmpty())
            MapFacade->setObjectName(QStringLiteral("MapFacade"));
        MapFacade->resize(400, 300);

        retranslateUi(MapFacade);

        QMetaObject::connectSlotsByName(MapFacade);
    } // setupUi

    void retranslateUi(QWidget *MapFacade)
    {
        MapFacade->setWindowTitle(QApplication::translate("MapFacade", "MapFacade", 0));
    } // retranslateUi

};

namespace Ui {
    class MapFacade: public Ui_MapFacade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPFACADE_H
