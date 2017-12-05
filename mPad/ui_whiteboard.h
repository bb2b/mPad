/********************************************************************************
** Form generated from reading UI file 'whiteboard.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITEBOARD_H
#define UI_WHITEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhiteBoard
{
public:

    void setupUi(QWidget *WhiteBoard)
    {
        if (WhiteBoard->objectName().isEmpty())
            WhiteBoard->setObjectName(QStringLiteral("WhiteBoard"));
        WhiteBoard->resize(400, 300);
        WhiteBoard->setStyleSheet(QStringLiteral("background:transparent;"));

        retranslateUi(WhiteBoard);

        QMetaObject::connectSlotsByName(WhiteBoard);
    } // setupUi

    void retranslateUi(QWidget *WhiteBoard)
    {
        WhiteBoard->setWindowTitle(QApplication::translate("WhiteBoard", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class WhiteBoard: public Ui_WhiteBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITEBOARD_H
