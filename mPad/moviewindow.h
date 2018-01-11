#ifndef MOVIEWINDOW_H
#define MOVIEWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QWidget>
#include <QSlider>
#include <QProcess>
#include <QTimer>

class MovieWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MovieWindow(QString moviepath, QWidget *parent = 0);
    ~MovieWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    static QVector<QString> g_movies;

public slots:
    void on_max_btn_clicked();
    void on_close_btn_clicked();
    void on_timer_out();
    void on_update_progress_slider();
    void on_volume_slider_valueChanged(int value);

private:
    bool b_move;
    QPoint m_last_point;
    QPushButton *m_max_btn;
    QPushButton *m_close_btn;
    QWidget *m_movie_widget;
    QSlider *m_progress;
    QSlider *m_volume;
    QProcess *m_player_process;
    QTimer *m_timer;
    QString m_moviepath;
};

#endif // MOVIEWINDOW_H
