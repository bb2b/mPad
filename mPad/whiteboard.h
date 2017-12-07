#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QLabel>
#include <QImage>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>

class WhiteBoard : public QLabel
{
    Q_OBJECT

public:
    WhiteBoard();
    ~WhiteBoard();

    void prepare(bool istransparent);
    void paint();
    void fullclear();
    void localclear();
    void revocation();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QImage m_image;
    QImage m_image_temp;
    QImage m_image_clear;
    QImage m_image_select;
    QImage *m_current_image;
    QPoint m_start_point;
    QPoint m_end_point;
    QPoint m_move_start_point;
    bool m_pressed;
    QVector<QPoint> points;
    QVector<QImage> images;
};

#endif // WHITEBOARD_H
