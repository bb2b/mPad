#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QPaintEvent>
#include <QMouseEvent>

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenShot(QWidget *parent = 0);
    ~ScreenShot();

    void prepare();
    void paint();

public slots:
    void on_close_button_clicked();
    void on_ok_button_clicked();
    void on_zoomin_button_clicked();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPushButton *m_close;
    QPushButton *m_ok;
    QPushButton *m_zoomin;
    bool m_pressed;
    bool m_disable_event;
    QImage m_image;
    QImage m_image_temp;
    QImage *m_image_current;
    QImage m_image_screenshot;
    QPoint m_start_point;
    QPoint m_end_point;
    QPixmap pixmap;
};

#endif // SCREENSHOT_H

