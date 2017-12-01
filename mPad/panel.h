#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class Panel;
}

class Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Panel *ui;
    bool b_move;
    QPoint m_last_point;
    QPoint m_absolute_point;
};

#endif // PANEL_H
