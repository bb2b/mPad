#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

namespace Ui {
class WhiteBoard;
}

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent = 0);
    ~WhiteBoard();

    void prepare(bool istransparent);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::WhiteBoard *ui;
    QImage m_image;
    QImage *m_current_image;
};

#endif // WHITEBOARD_H
