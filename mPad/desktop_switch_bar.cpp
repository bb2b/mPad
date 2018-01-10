#include "desktop_switch_bar.h"
#include "global.h"

DesktopSwitchBar::DesktopSwitchBar(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 120, 120, 60, 60);
    this->setStyleSheet("background-color:rgb(134,134,134);");
}

DesktopSwitchBar::~DesktopSwitchBar()
{
}

void DesktopSwitchBar::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
    m_absolute_point = event->globalPos();
}

void DesktopSwitchBar::mouseMoveEvent(QMouseEvent *event)
{
    if (b_move)
        this->move(this->pos() + event->pos() - m_last_point);
}

void DesktopSwitchBar::mouseReleaseEvent(QMouseEvent *event)
{
    b_move = false;

    //如果未移动，则判定为点击
    if(m_absolute_point == event->globalPos())
    {
        if(g_mainwindow->isMinimized())
        {
            g_mainwindow->showFullScreen();
            set_window_top_hint(g_whiteboard, HWND_TOP, true);
        }
        else
        {
            g_mainwindow->showMinimized();
            g_whiteboard->move(0, -g_whiteboard->height());
            set_window_top_hint(g_whiteboard, HWND_BOTTOM, false);
            g_notebar->on_painttoolbar(true);
        }
    }
}
