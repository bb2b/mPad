#include "explorerwindow.h"
#include "global.h"

QVector<QString> ExplorerWindow::g_files(0);

ExplorerWindow::ExplorerWindow(QString filepath, QWidget *parent) : QWidget(parent)
{
    ExplorerWindow::g_files.push_back(filepath);
}

ExplorerWindow::~ExplorerWindow()
{

}

void ExplorerWindow::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
}

void ExplorerWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint new_point = this->pos() + event->pos() - m_last_point;
    if(b_move && new_point.x() >= 0 && new_point.x() + this->width() <= GetSystemMetrics(SM_CXSCREEN) && new_point.y() >= 0 && new_point.y() + this->height() <= GetSystemMetrics(SM_CYSCREEN))
    {
        this->move(new_point);
    }
    else
        m_last_point = event->pos();
}

void ExplorerWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    b_move = false;
}
