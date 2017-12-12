#ifndef MYLABEL
#define MYLABEL
#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
Q_OBJECT

public:
    explicit myLabel(QWidget *parent = 0);
    ~myLabel();

signals:
    void clicked();
    void right_clicked();
    void double_clicked();

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MYLABEL

