#ifndef NOTEBAR_H
#define NOTEBAR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include "mylabel.h"

class PaintToolBar;

class NoteBar : public QWidget
{
    Q_OBJECT

public:
    explicit NoteBar(QWidget *parent = 0);
    ~NoteBar();

    void on_painttoolbar(bool flag);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool b_move;
    QPoint m_last_point;
    QPoint m_absolute_point;
    PaintToolBar *g_painttoolbar;
};

class PaintToolBar : public QLabel
{
    Q_OBJECT

public:
    PaintToolBar();
    ~PaintToolBar();

    void on_point_clear();
    void on_color_clear();
    void on_point_set();
    void on_color_set();

public slots:
    void on_roaming_clicked();
    void on_select_clicked();
    void on_fullsave_clicked();
    void on_localsave_clicked();
    void on_fullclear_clicked();
    void on_localclear_clicked();
    void on_revocation_clicked();
    void on_brush_clicked();
    void on_spoint_clicked();
    void on_mpoint_clicked();
    void on_bpoint_clicked();
    void on_red_clicked();
    void on_darkblue_clicked();
    void on_darkgreen_clicked();
    void on_orange_clicked();
    void on_black_clicked();
    void on_white_clicked();
    void on_yellow_clicked();
    void on_lightgreen_clicked();
    void on_lightblue_clicked();

private:
    QVBoxLayout *v_layout;
    QFrame *h_frame_1;
    QFrame *h_frame_2;
    QFrame *g_frame;
    QHBoxLayout *h_layout_1;
    QHBoxLayout *h_layout_2;
    QGridLayout *g_layout;
    myLabel *x_roaming;
    myLabel *x_select;
    myLabel *x_fullsave;
    myLabel *x_localsave;
    myLabel *x_fullclear;
    myLabel *x_localclear;
    myLabel *x_revocation;
    myLabel *x_brush;
    myLabel *x_sPoint;
    myLabel *x_mPoint;
    myLabel *x_bPoint;
    myLabel *x_red;
    myLabel *x_darkblue;
    myLabel *x_darkgreen;
    myLabel *x_orange;
    myLabel *x_black;
    myLabel *x_white;
    myLabel *x_yellow;
    myLabel *x_lightgreen;
    myLabel *x_lightblue;
};

#endif // NOTEBAR_H
