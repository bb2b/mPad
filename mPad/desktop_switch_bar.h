#ifndef DESKTOP_SWITCH_BAR_H
#define DESKTOP_SWITCH_BAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class DesktopSwitchBar : public QWidget
{
    Q_OBJECT

public:
    explicit DesktopSwitchBar(QWidget *parent = 0);
    ~DesktopSwitchBar();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool b_move;
    QPoint m_last_point;
    QPoint m_absolute_point;
};

#endif // DESKTOP_SWITCH_BAR_H
