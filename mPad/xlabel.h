#ifndef XLABEL
#define XLABEL
#include <QLabel>
#include <QMouseEvent>

class XLabel : public QLabel
{
Q_OBJECT

public:
    XLabel(QWidget *parent);
    ~XLabel();

signals:
    void clicked();
    void right_clicked();
    void double_clicked();

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // XLABEL

