#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QImage>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QColor>
#include <QPoint>

class WhiteBoard : public QLabel
{
    Q_OBJECT

public:
    WhiteBoard();
    ~WhiteBoard();

    void prepare(bool istransparent);
    void paint();
    void fullclear();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::WhiteBoard *ui;
    QImage m_image;
    QImage *m_current_image;
    QPoint m_start_point;
    QPoint m_end_point;
    QPoint m_move_start_point;
    bool m_pressed;
};

#endif // WHITEBOARD_H
