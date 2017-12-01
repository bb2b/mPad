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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoteBar
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *NotePanel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *roaming;
    QLabel *select;
    QLabel *fullscreenSave;
    QLabel *screenshotSave;
    QLabel *clearscreen;
    QLabel *localclear;
    QLabel *revocation;
    QLabel *brush;
    QHBoxLayout *horizontalLayout_2;
    QLabel *smallpoint;
    QLabel *middlepoint;
    QLabel *bigpoint;
    QGridLayout *gridLayout;
    QLabel *darkblue;
    QLabel *darkgreen;
    QLabel *orange;
    QLabel *black;
    QLabel *white;
    QLabel *red;
    QLabel *yellow;
    QLabel *lightgreen;
    QLabel *lightblue;
    QPushButton *NoteButton;

    void setupUi(QWidget *NoteBar)
    {
        if (NoteBar->objectName().isEmpty())
            NoteBar->setObjectName(QStringLiteral("NoteBar"));
        NoteBar->resize(86, 594);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NoteBar->sizePolicy().hasHeightForWidth());
        NoteBar->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(NoteBar);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        NotePanel = new QFrame(NoteBar);
        NotePanel->setObjectName(QStringLiteral("NotePanel"));
        NotePanel->setFrameShape(QFrame::StyledPanel);
        NotePanel->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(NotePanel);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        roaming = new QLabel(NotePanel);
        roaming->setObjectName(QStringLiteral("roaming"));
        roaming->setScaledContents(false);
        roaming->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(roaming);

        select = new QLabel(NotePanel);
        select->setObjectName(QStringLiteral("select"));
        select->setScaledContents(false);
        select->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(select);


        verticalLayout_2->addLayout(horizontalLayout);

        fullscreenSave = new QLabel(NotePanel);
        fullscreenSave->setObjectName(QStringLiteral("fullscreenSave"));
        fullscreenSave->setScaledContents(false);
        fullscreenSave->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(fullscreenSave);

        screenshotSave = new QLabel(NotePanel);
        screenshotSave->setObjectName(QStringLiteral("screenshotSave"));
        screenshotSave->setScaledContents(false);
        screenshotSave->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(screenshotSave);

        clearscreen = new QLabel(NotePanel);
        clearscreen->setObjectName(QStringLiteral("clearscreen"));
        clearscreen->setScaledContents(false);
        clearscreen->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(clearscreen);

        localclear = new QLabel(NotePanel);
        localclear->setObjectName(QStringLiteral("localclear"));
        localclear->setScaledContents(false);
        localclear->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(localclear);

        revocation = new QLabel(NotePanel);
        revocation->setObjectName(QStringLiteral("revocation"));
        revocation->setScaledContents(false);
        revocation->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(revocation);

        brush = new QLabel(NotePanel);
        brush->setObjectName(QStringLiteral("brush"));
        brush->setScaledContents(false);
        brush->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(brush);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        smallpoint = new QLabel(NotePanel);
        smallpoint->setObjectName(QStringLiteral("smallpoint"));
        smallpoint->setScaledContents(false);
        smallpoint->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(smallpoint);

        middlepoint = new QLabel(NotePanel);
        middlepoint->setObjectName(QStringLiteral("middlepoint"));
        middlepoint->setScaledContents(false);
        middlepoint->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(middlepoint);

        bigpoint = new QLabel(NotePanel);
        bigpoint->setObjectName(QStringLiteral("bigpoint"));
        bigpoint->setScaledContents(false);
        bigpoint->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(bigpoint);


        verticalLayout_2->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        darkblue = new QLabel(NotePanel);
        darkblue->setObjectName(QStringLiteral("darkblue"));
        darkblue->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 255);"));
        darkblue->setScaledContents(false);

        gridLayout->addWidget(darkblue, 0, 1, 1, 1);

        darkgreen = new QLabel(NotePanel);
        darkgreen->setObjectName(QStringLiteral("darkgreen"));
        darkgreen->setStyleSheet(QStringLiteral("background-color: rgb(0, 170, 0);"));
        darkgreen->setScaledContents(false);

        gridLayout->addWidget(darkgreen, 0, 2, 1, 1);

        orange = new QLabel(NotePanel);
        orange->setObjectName(QStringLiteral("orange"));
        orange->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));
        orange->setScaledContents(false);

        gridLayout->addWidget(orange, 1, 0, 1, 1);

        black = new QLabel(NotePanel);
        black->setObjectName(QStringLiteral("black"));
        black->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        black->setScaledContents(false);

        gridLayout->addWidget(black, 1, 1, 1, 1);

        white = new QLabel(NotePanel);
        white->setObjectName(QStringLiteral("white"));
        white->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        white->setScaledContents(false);

        gridLayout->addWidget(white, 1, 2, 1, 1);

        red = new QLabel(NotePanel);
        red->setObjectName(QStringLiteral("red"));
        red->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        red->setScaledContents(false);

        gridLayout->addWidget(red, 0, 0, 1, 1);

        yellow = new QLabel(NotePanel);
        yellow->setObjectName(QStringLiteral("yellow"));
        yellow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
        yellow->setScaledContents(false);

        gridLayout->addWidget(yellow, 2, 0, 1, 1);

        lightgreen = new QLabel(NotePanel);
        lightgreen->setObjectName(QStringLiteral("lightgreen"));
        lightgreen->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 0);"));
        lightgreen->setScaledContents(false);

        gridLayout->addWidget(lightgreen, 2, 1, 1, 1);

        lightblue = new QLabel(NotePanel);
        lightblue->setObjectName(QStringLiteral("lightblue"));
        lightblue->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        lightblue->setScaledContents(false);

        gridLayout->addWidget(lightblue, 2, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addWidget(NotePanel);

        NoteButton = new QPushButton(NoteBar);
        NoteButton->setObjectName(QStringLiteral("NoteButton"));

        verticalLayout->addWidget(NoteButton);


        retranslateUi(NoteBar);

        QMetaObject::connectSlotsByName(NoteBar);
    } // setupUi

    void retranslateUi(QWidget *NoteBar)
    {
        NoteBar->setWindowTitle(QApplication::translate("NoteBar", "Form", 0));
        roaming->setText(QApplication::translate("NoteBar", "\346\274\253\346\270\270", 0));
        select->setText(QApplication::translate("NoteBar", "\345\234\210\351\200\211", 0));
        fullscreenSave->setText(QApplication::translate("NoteBar", "\345\205\250\345\261\217\344\277\235\345\255\230", 0));
        screenshotSave->setText(QApplication::translate("NoteBar", "\346\210\252\345\261\217\344\277\235\345\255\230", 0));
        clearscreen->setText(QApplication::translate("NoteBar", "\346\270\205\345\261\217", 0));
        localclear->setText(QApplication::translate("NoteBar", "\345\261\200\351\203\250\346\270\205\351\231\244", 0));
        revocation->setText(QApplication::translate("NoteBar", "\346\222\244\351\224\200", 0));
        brush->setText(QApplication::translate("NoteBar", "\347\224\273\347\254\224", 0));
        smallpoint->setText(QApplication::translate("NoteBar", "\345\260\217\347\202\271", 0));
        middlepoint->setText(QApplication::translate("NoteBar", "\344\270\255\347\202\271", 0));
        bigpoint->setText(QApplication::translate("NoteBar", "\345\244\247\347\202\271", 0));
        darkblue->setText(QString());
        darkgreen->setText(QString());
        orange->setText(QString());
        black->setText(QString());
        white->setText(QString());
        red->setText(QString());
        yellow->setText(QString());
        lightgreen->setText(QString());
        lightblue->setText(QString());
        NoteButton->setText(QApplication::translate("NoteBar", "\346\211\271\346\263\250", 0));
    } // retranslateUi

};

namespace Ui {
    class NoteBar: public Ui_NoteBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEBAR_H
