#include "panel.h"
#include "ui_panel.h"
#include "global.h"

Panel::Panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 120, 120, 60, 60);
}

Panel::~Panel()
{
    delete ui;
}

void Panel::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
    m_absolute_point = event->globalPos();
}

void Panel::mouseMoveEvent(QMouseEvent *event)
{
    if (b_move)
        this->move(this->pos() + event->pos() - m_last_point);
}

void Panel::mouseReleaseEvent(QMouseEvent *event)
{
    b_move = false;

    //���δ�ƶ������ж�Ϊ���
    if(m_absolute_point == event->globalPos())
    {
        if(g_mainwindow->isMinimized())
            g_mainwindow->showFullScreen();
        else
            g_mainwindow->showMinimized();
    }
}
