#ifndef PICTUREWINDOW_H
#define PICTUREWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QPixmap>

class PictureWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PictureWindow(QString picpath, QWidget *parent = 0);
    ~PictureWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    static QVector<QString> g_pictures;

public slots:
    void on_close_btn_clicked();

private:
    bool b_move;
    QPoint m_last_point;
    QLabel *m_display;
    QPushButton *m_close_btn;
    QString m_picpath;
    QPixmap *m_pixmap;
};

#endif // PICTUREWINDOW_H
