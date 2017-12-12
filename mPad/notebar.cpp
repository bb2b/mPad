#include "notebar.h"
#include "global.h"

NoteBar::NoteBar(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 120, GetSystemMetrics(SM_CYSCREEN) - 120, 60, 60);

    g_painttoolbar = new PaintToolBar;
    set_window_top_hint(g_painttoolbar, HWND_TOPMOST, true);
    g_painttoolbar->hide();
}

NoteBar::~NoteBar()
{
    delete g_painttoolbar;
}

void NoteBar::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
    m_absolute_point = event->globalPos();
}

void NoteBar::mouseMoveEvent(QMouseEvent *event)
{
    if(b_move)
    {
        this->move(this->pos() + event->pos() - m_last_point);
        if(g_painttoolbar->isVisible())
            g_painttoolbar->move(g_painttoolbar->pos() + event->pos() - m_last_point);
    }
}

void NoteBar::mouseReleaseEvent(QMouseEvent *event)
{
    b_move = false;

    //如果未移动，则判定为点击
    if(m_absolute_point == event->globalPos())
    {
        on_painttoolbar(g_painttoolbar->isVisible());
    }
}

void NoteBar::on_painttoolbar(bool flag)
{
    if(flag)
    {
        g_painttoolbar->hide();
        g_whiteboard->move(0, -g_whiteboard->height());
        set_window_top_hint(g_whiteboard, HWND_BOTTOM, false);
    }
    else
    {
        g_painttoolbar->setGeometry(this->pos().x(), this->pos().y() - 410, 60, 410);
        g_painttoolbar->on_brush_clicked();
        g_painttoolbar->show();
        g_whiteboard->prepare(true);
        g_whiteboard->move(0,0);
        set_window_top_hint(g_whiteboard, HWND_TOP, true);
    }
}

PaintToolBar::PaintToolBar()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

    v_layout = new QVBoxLayout;
    v_layout->setSpacing(0);
    v_layout->setContentsMargins(0,0,0,0);
    h_layout_1 = new QHBoxLayout;
    h_layout_1->setSpacing(0);
    h_layout_1->setContentsMargins(0,0,0,0);
    h_layout_2 = new QHBoxLayout;
    h_layout_2->setSpacing(0);
    h_layout_2->setContentsMargins(0,0,0,0);
    g_layout = new QGridLayout;
    g_layout->setSpacing(0);
    g_layout->setContentsMargins(0,0,0,0);

    h_frame_1 = new QFrame;
    h_frame_2 = new QFrame;
    g_frame = new QFrame;

    QTextCodec *codec = QTextCodec::codecForName("GBK");
    x_roaming = new myLabel(NULL);
    connect(x_roaming, SIGNAL(clicked()), this, SLOT(on_roaming_clicked()));
    x_roaming->setFixedSize(30, 30);
    x_roaming->setText(codec->toUnicode("漫游"));
    x_roaming->setFrameShape(QFrame::Box);
    x_select = new myLabel(NULL);
    connect(x_select, SIGNAL(clicked()), this, SLOT(on_select_clicked()));
    x_select->setFixedSize(30, 30);
    x_select->setText(codec->toUnicode("圈选"));
    x_select->setFrameShape(QFrame::Box);
    x_fullsave = new myLabel(NULL);
    connect(x_fullsave, SIGNAL(clicked()), this, SLOT(on_fullsave_clicked()));
    x_fullsave->setFixedSize(60, 50);
    x_fullsave->setText(codec->toUnicode("全屏保存"));
    x_localsave = new myLabel(NULL);
    connect(x_localsave, SIGNAL(clicked()), this, SLOT(on_localsave_clicked()));
    x_localsave->setFixedSize(60, 50);
    x_localsave->setText(codec->toUnicode("截屏保存"));
    x_fullclear = new myLabel(NULL);
    connect(x_fullclear, SIGNAL(clicked()), this, SLOT(on_fullclear_clicked()));
    x_fullclear->setFixedSize(60, 50);
    x_fullclear->setText(codec->toUnicode("清屏"));
    x_localclear = new myLabel(NULL);
    connect(x_localclear, SIGNAL(clicked()), this, SLOT(on_localclear_clicked()));
    x_localclear->setFixedSize(60, 50);
    x_localclear->setText(codec->toUnicode("局部清除"));
    x_revocation = new myLabel(NULL);
    connect(x_revocation, SIGNAL(clicked()), this, SLOT(on_revocation_clicked()));
    x_revocation->setFixedSize(60, 50);
    x_revocation->setText(codec->toUnicode("撤销"));
    x_brush = new myLabel(NULL);
    connect(x_brush, SIGNAL(clicked()), this, SLOT(on_brush_clicked()));
    x_brush->setFixedSize(60, 50);
    x_brush->setText(codec->toUnicode("画刷"));
    x_brush->setFrameShape(QFrame::Box);
    x_sPoint = new myLabel(NULL);
    connect(x_sPoint, SIGNAL(clicked()), this, SLOT(on_spoint_clicked()));
    x_sPoint->setFixedSize(20, 20);
    x_sPoint->setText(codec->toUnicode("小"));
    x_sPoint->setFrameShape(QFrame::Box);
    x_mPoint = new myLabel(NULL);
    connect(x_mPoint, SIGNAL(clicked()), this, SLOT(on_mpoint_clicked()));
    x_mPoint->setFixedSize(20, 20);
    x_mPoint->setText(codec->toUnicode("中"));
    x_mPoint->setFrameShape(QFrame::Box);
    x_bPoint = new myLabel(NULL);
    connect(x_bPoint, SIGNAL(clicked()), this, SLOT(on_bpoint_clicked()));
    x_bPoint->setFixedSize(20, 20);
    x_bPoint->setText(codec->toUnicode("大"));
    x_bPoint->setFrameShape(QFrame::Box);
    x_red = new myLabel(NULL);
    connect(x_red, SIGNAL(clicked()), this, SLOT(on_red_clicked()));
    x_red->setFixedSize(20, 20);
    x_red->setStyleSheet("background-color:rgb(255,0,0);");
    x_red->setFrameShape(QFrame::Box);
    x_darkblue = new myLabel(NULL);
    connect(x_darkblue, SIGNAL(clicked()), this, SLOT(on_darkblue_clicked()));
    x_darkblue->setFixedSize(20, 20);
    x_darkblue->setStyleSheet("background-color:rgb(0,0,255);");
    x_darkblue->setFrameShape(QFrame::Box);
    x_darkgreen = new myLabel(NULL);
    connect(x_darkgreen, SIGNAL(clicked()), this, SLOT(on_darkgreen_clicked()));
    x_darkgreen->setFixedSize(20, 20);
    x_darkgreen->setStyleSheet("background-color:rgb(0,128,0);");
    x_darkgreen->setFrameShape(QFrame::Box);
    x_orange = new myLabel(NULL);
    connect(x_orange, SIGNAL(clicked()), this, SLOT(on_orange_clicked()));
    x_orange->setFixedSize(20, 20);
    x_orange->setStyleSheet("background-color:rgb(255,128,0);");
    x_orange->setFrameShape(QFrame::Box);
    x_black = new myLabel(NULL);
    connect(x_black, SIGNAL(clicked()), this, SLOT(on_black_clicked()));
    x_black->setFixedSize(20, 20);
    x_black->setStyleSheet("background-color:rgb(0,0,0);");
    x_black->setFrameShape(QFrame::Box);
    x_white = new myLabel(NULL);
    connect(x_white, SIGNAL(clicked()), this, SLOT(on_white_clicked()));
    x_white->setFixedSize(20, 20);
    x_white->setStyleSheet("background-color:rgb(255,255,255);");
    x_white->setFrameShape(QFrame::Box);
    x_yellow = new myLabel(NULL);
    connect(x_yellow, SIGNAL(clicked()), this, SLOT(on_yellow_clicked()));
    x_yellow->setFixedSize(20, 20);
    x_yellow->setStyleSheet("background-color:rgb(255,255,0);");
    x_yellow->setFrameShape(QFrame::Box);
    x_lightgreen = new myLabel(NULL);
    connect(x_lightgreen, SIGNAL(clicked()), this, SLOT(on_lightgreen_clicked()));
    x_lightgreen->setFixedSize(20, 20);
    x_lightgreen->setStyleSheet("background-color:rgb(0,255,0);");
    x_lightgreen->setFrameShape(QFrame::Box);
    x_lightblue = new myLabel(NULL);
    connect(x_lightblue, SIGNAL(clicked()), this, SLOT(on_lightblue_clicked()));
    x_lightblue->setFixedSize(20, 20);
    x_lightblue->setStyleSheet("background-color:rgb(0,128,255);");
    x_lightblue->setFrameShape(QFrame::Box);

    h_layout_1->addWidget(x_roaming);
    h_layout_1->addWidget(x_select);
    h_layout_2->addWidget(x_sPoint);
    h_layout_2->addWidget(x_mPoint);
    h_layout_2->addWidget(x_bPoint);
    g_layout->addWidget(x_red, 0, 0);
    g_layout->addWidget(x_darkblue, 0, 1);
    g_layout->addWidget(x_darkgreen, 0, 2);
    g_layout->addWidget(x_orange, 1, 0);
    g_layout->addWidget(x_black, 1, 1);
    g_layout->addWidget(x_white, 1, 2);
    g_layout->addWidget(x_yellow, 2, 0);
    g_layout->addWidget(x_lightgreen, 2, 1);
    g_layout->addWidget(x_lightblue, 2, 2);
    h_frame_1->setLayout(h_layout_1);
    h_frame_2->setLayout(h_layout_2);
    g_frame->setLayout(g_layout);
    v_layout->addWidget(h_frame_1);
    v_layout->addWidget(x_fullsave);
    v_layout->addWidget(x_localsave);
    v_layout->addWidget(x_fullclear);
    v_layout->addWidget(x_localclear);
    v_layout->addWidget(x_revocation);
    v_layout->addWidget(x_brush);
    v_layout->addWidget(h_frame_2);
    v_layout->addWidget(g_frame);

    this->setLayout(v_layout);
}

PaintToolBar::~PaintToolBar()
{
    delete x_roaming;
    delete x_select;
    delete x_fullsave;
    delete x_localsave;
    delete x_fullclear;
    delete x_localclear;
    delete x_revocation;
    delete x_brush;
    delete x_sPoint;
    delete x_mPoint;
    delete x_bPoint;
    delete x_red;
    delete x_darkblue;
    delete x_darkgreen;
    delete x_orange;
    delete x_black;
    delete x_white;
    delete x_yellow;
    delete x_lightgreen;
    delete x_lightblue;

    delete h_layout_1;
    delete h_layout_2;
    delete g_layout;
    delete h_frame_1;
    delete h_frame_2;
    delete g_frame;
    delete v_layout;
}

void PaintToolBar::on_point_clear()
{
    x_sPoint->setStyleSheet("border:none;");
    x_mPoint->setStyleSheet("border:none;");
    x_bPoint->setStyleSheet("border:none;");
}

void PaintToolBar::on_color_clear()
{
    x_red->setStyleSheet("border:none;background-color:rgb(255,0,0);");
    x_darkblue->setStyleSheet("border:none;background-color:rgb(0,0,255);");
    x_darkgreen->setStyleSheet("border:none;background-color:rgb(0,128,0);");
    x_orange->setStyleSheet("border:none;background-color:rgb(255,128,0);");
    x_black->setStyleSheet("border:none;background-color:rgb(0,0,0);");
    x_white->setStyleSheet("border:none;background-color:rgb(255,255,255);");
    x_yellow->setStyleSheet("border:none;background-color:rgb(255,255,0);");
    x_lightgreen->setStyleSheet("border:none;background-color:rgb(0,255,0);");
    x_lightblue->setStyleSheet("border:none;background-color:rgb(0,128,255);");
}

void PaintToolBar::on_point_set()
{
    g_draw_type = DRAW;

    if(g_draw_width == 1)
        x_sPoint->setStyleSheet("border:3px solid rgb(0,0,0);");
    else if(g_draw_width == 2)
        x_mPoint->setStyleSheet("border:3px solid rgb(0,0,0);");
    else if(g_draw_width == 3)
        x_bPoint->setStyleSheet("border:3px solid rgb(0,0,0);");
}

void PaintToolBar::on_color_set()
{
    g_draw_type = DRAW;

    if(g_draw_color == QColor(0,0,0,0))
        g_draw_color = QColor(255,0,0);

    if(g_draw_color == QColor(255,0,0))
        x_red->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(255,0,0);");
    else if(g_draw_color == QColor(0,0,255))
        x_darkblue->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(0,0,255);");
    else if(g_draw_color == QColor(0,128,0))
        x_darkgreen->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(0,128,0);");
    else if(g_draw_color == QColor(255,128,0))
        x_orange->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(255,128,0);");
    else if(g_draw_color == QColor(0,0,0))
        x_black->setStyleSheet("border:3px solid rgb(192,192,192);background-color:rgb(0,0,0);");
    else if(g_draw_color == QColor(255,255,255))
        x_white->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(255,255,255);");
    else if(g_draw_color == QColor(255,255,0))
        x_yellow->setStyleSheet("border:3px solid rgb(0,0,02);background-color:rgb(255,255,0);");
    else if(g_draw_color == QColor(0,255,0))
        x_lightgreen->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(0,255,0);");
    else if(g_draw_color == QColor(0,128,255))
        x_lightblue->setStyleSheet("border:3px solid rgb(0,0,0);background-color:rgb(0,128,255);");
}

void PaintToolBar::on_roaming_clicked()
{
    x_roaming->setStyleSheet("border:3px solid rgb(0,0,0);");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:none;");
    on_point_clear();
    on_color_clear();

    g_draw_type = ROAMING;
}

void PaintToolBar::on_select_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:3px solid rgb(0,0,0);");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:none;");
    on_point_clear();
    on_color_clear();

    g_draw_type = SELECT;
}

void PaintToolBar::on_fullsave_clicked()
{
    g_desktopswitchbar->hide();
    g_notebar->hide();
    g_switchboard->hide();
    QPixmap pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    QString savepath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    savepath += generate_name_by_current_time();
    pixmap.save(savepath, "JPG", 100);
    g_desktopswitchbar->show();
    g_notebar->show();
    g_switchboard->show();
}

void PaintToolBar::on_localsave_clicked()
{
    g_screenshot->prepare();
    g_screenshot->show();
    set_window_top_hint(g_screenshot, HWND_TOPMOST, true);
}

void PaintToolBar::on_fullclear_clicked()
{
    g_whiteboard->fullclear();
}

void PaintToolBar::on_localclear_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:3px solid rgb(0,0,0);");
    x_brush->setStyleSheet("border:none;");
    on_point_clear();
    on_color_clear();

    //g_whiteboard->localclear();
    g_draw_type = ERASE;
}

void PaintToolBar::on_revocation_clicked()
{
    g_whiteboard->revocation();
}

void PaintToolBar::on_brush_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    on_point_clear();
    on_color_clear();
    on_point_set();
    on_color_set();
}

void PaintToolBar::on_spoint_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_width = 1;
    on_point_clear();
    on_point_set();
    on_color_set();
}

void PaintToolBar::on_mpoint_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_width = 2;
    on_point_clear();
    on_point_set();
    on_color_set();
}

void PaintToolBar::on_bpoint_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_width = 3;
    on_point_clear();
    on_point_set();
    on_color_set();
}

void PaintToolBar::on_red_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(255,0,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_darkblue_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(0,0,255);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_darkgreen_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(0,128,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_orange_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(255,128,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_black_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(0,0,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_white_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(255,255,255);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_yellow_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(255,255,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_lightgreen_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(0,255,0);
    on_color_clear();
    on_color_set();
    on_point_set();
}

void PaintToolBar::on_lightblue_clicked()
{
    x_roaming->setStyleSheet("border:none;");
    x_select->setStyleSheet("border:none;");
    x_localclear->setStyleSheet("border:none;");
    x_brush->setStyleSheet("border:3px solid rgb(0,0,0);");

    g_draw_color = QColor(0,128,255);
    on_color_clear();
    on_color_set();
    on_point_set();
}
