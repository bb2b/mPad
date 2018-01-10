#include "mylabel.h"

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    this->setAlignment(Qt::AlignCenter);
    //this->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(209, 209, 209, 255), stop:1 rgba(253, 253, 253, 255));");
}

myLabel::~myLabel()
{
}

void myLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    if (event->button() == Qt::RightButton) {
        emit right_clicked();
    }
    QLabel::mousePressEvent(event);
}

void myLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit double_clicked();
}
