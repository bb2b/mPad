/********************************************************************************
** Form generated from reading UI file 'notebar.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEBAR_H
#define UI_NOTEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoteBar
{
public:

    void setupUi(QWidget *NoteBar)
    {
        if (NoteBar->objectName().isEmpty())
            NoteBar->setObjectName(QStringLiteral("NoteBar"));
        NoteBar->resize(400, 300);

        retranslateUi(NoteBar);

        QMetaObject::connectSlotsByName(NoteBar);
    } // setupUi

    void retranslateUi(QWidget *NoteBar)
    {
        NoteBar->setWindowTitle(QApplication::translate("NoteBar", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class NoteBar: public Ui_NoteBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEBAR_H
