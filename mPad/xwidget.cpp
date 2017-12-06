#include "xwidget.h"

XLabel::XLabel(QWidget *parent) : QLabel(parent)
{
    this->setAlignment(Qt::AlignCenter);
}

XLabel::~XLabel()
{
}

void XLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    if (event->button() == Qt::RightButton) {
        emit right_clicked();
    }
    QLabel::mousePressEvent(event);
}

void XLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit double_clicked();
}
