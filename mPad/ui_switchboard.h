/********************************************************************************
** Form generated from reading UI file 'switchboard.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHBOARD_H
#define UI_SWITCHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SwitchBoard
{
public:

    void setupUi(QWidget *SwitchBoard)
    {
        if (SwitchBoard->objectName().isEmpty())
            SwitchBoard->setObjectName(QStringLiteral("SwitchBoard"));
        SwitchBoard->resize(400, 300);

        retranslateUi(SwitchBoard);

        QMetaObject::connectSlotsByName(SwitchBoard);
    } // setupUi

    void retranslateUi(QWidget *SwitchBoard)
    {
        SwitchBoard->setWindowTitle(QApplication::translate("SwitchBoard", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SwitchBoard: public Ui_SwitchBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHBOARD_H
