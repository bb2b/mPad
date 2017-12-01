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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SwitchBoard
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *SwitchBoard)
    {
        if (SwitchBoard->objectName().isEmpty())
            SwitchBoard->setObjectName(QStringLiteral("SwitchBoard"));
        SwitchBoard->resize(75, 23);
        verticalLayout = new QVBoxLayout(SwitchBoard);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(SwitchBoard);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(SwitchBoard);

        QMetaObject::connectSlotsByName(SwitchBoard);
    } // setupUi

    void retranslateUi(QWidget *SwitchBoard)
    {
        SwitchBoard->setWindowTitle(QApplication::translate("SwitchBoard", "Form", 0));
        pushButton->setText(QApplication::translate("SwitchBoard", "\344\270\213\346\213\211", 0));
    } // retranslateUi

};

namespace Ui {
    class SwitchBoard: public Ui_SwitchBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHBOARD_H
