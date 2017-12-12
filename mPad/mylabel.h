#ifndef MYLABEL
#define MYLABEL
#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
Q_OBJECT

public:
    myLabel(QWidget *parent);
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

