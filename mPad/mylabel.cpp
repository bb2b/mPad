#include "mylabel.h"

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    this->setAlignment(Qt::AlignCenter);
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
