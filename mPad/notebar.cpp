#include "notebar.h"
#include "ui_notebar.h"
#include "global.h"

NoteBar::NoteBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteBar)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 120, GetSystemMetrics(SM_CYSCREEN) - 120, 60, 60);

    g_painttoolbar = new PaintToolBar;
    set_window_top_hint(g_painttoolbar, HWND_TOPMOST, true);
    g_painttoolbar->hide();
}

NoteBar::~NoteBar()
{
    delete ui;
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

    //���δ�ƶ������ж�Ϊ���
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
    x_roaming = new XLabel(NULL);
    connect(x_roaming, SIGNAL(clicked()), this, SLOT(on_roaming_clicked()));
    x_roaming->setFixedSize(30, 30);
    x_roaming->setText(codec->toUnicode("����"));
    x_select = new XLabel(NULL);
    connect(x_select, SIGNAL(clicked()), this, SLOT(on_select_clicked()));
    x_select->setFixedSize(30, 30);
    x_select->setText(codec->toUnicode("Ȧѡ"));
    x_fullsave = new XLabel(NULL);
    connect(x_fullsave, SIGNAL(clicked()), this, SLOT(on_fullsave_clicked()));
    x_fullsave->setFixedSize(60, 50);
    x_fullsave->setText(codec->toUnicode("ȫ������"));
    x_localsave = new XLabel(NULL);
    connect(x_localsave, SIGNAL(clicked()), this, SLOT(on_localsave_clicked()));
    x_localsave->setFixedSize(60, 50);
    x_localsave->setText(codec->toUnicode("��������"));
    x_fullclear = new XLabel(NULL);
    connect(x_fullclear, SIGNAL(clicked()), this, SLOT(on_fullclear_clicked()));
    x_fullclear->setFixedSize(60, 50);
    x_fullclear->setText(codec->toUnicode("����"));
    x_localclear = new XLabel(NULL);
    connect(x_localclear, SIGNAL(clicked()), this, SLOT(on_localclear_clicked()));
    x_localclear->setFixedSize(60, 50);
    x_localclear->setText(codec->toUnicode("�ֲ����"));
    x_revocation = new XLabel(NULL);
    connect(x_revocation, SIGNAL(clicked()), this, SLOT(on_revocation_clicked()));
    x_revocation->setFixedSize(60, 50);
    x_revocation->setText(codec->toUnicode("����"));
    x_brush = new XLabel(NULL);
    connect(x_brush, SIGNAL(clicked()), this, SLOT(on_brush_clicked()));
    x_brush->setFixedSize(60, 50);
    x_brush->setText(codec->toUnicode("��ˢ"));
    x_sPoint = new XLabel(NULL);
    connect(x_sPoint, SIGNAL(clicked()), this, SLOT(on_spoint_clicked()));
    x_sPoint->setFixedSize(20, 20);
    x_sPoint->setText(codec->toUnicode("С"));
    x_mPoint = new XLabel(NULL);
    connect(x_mPoint, SIGNAL(clicked()), this, SLOT(on_mpoint_clicked()));
    x_mPoint->setFixedSize(20, 20);
    x_mPoint->setText(codec->toUnicode("��"));
    x_bPoint = new XLabel(NULL);
    connect(x_bPoint, SIGNAL(clicked()), this, SLOT(on_bpoint_clicked()));
    x_bPoint->setFixedSize(20, 20);
    x_bPoint->setText(codec->toUnicode("��"));
    x_red = new XLabel(NULL);
    connect(x_red, SIGNAL(clicked()), this, SLOT(on_red_clicked()));
    x_red->setFixedSize(20, 20);
    x_red->setStyleSheet("background-color:rgb(255,0,0);");
    x_darkblue = new XLabel(NULL);
    connect(x_darkblue, SIGNAL(clicked()), this, SLOT(on_darkblue_clicked()));
    x_darkblue->setFixedSize(20, 20);
    x_darkblue->setStyleSheet("background-color:rgb(0,0,255);");
    x_darkgreen = new XLabel(NULL);
    connect(x_darkgreen, SIGNAL(clicked()), this, SLOT(on_darkgreen_clicked()));
    x_darkgreen->setFixedSize(20, 20);
    x_darkgreen->setStyleSheet("background-color:rgb(0,128,0);");
    x_orange = new XLabel(NULL);
    connect(x_orange, SIGNAL(clicked()), this, SLOT(on_orange_clicked()));
    x_orange->setFixedSize(20, 20);
    x_orange->setStyleSheet("background-color:rgb(255,128,0);");
    x_black = new XLabel(NULL);
    connect(x_black, SIGNAL(clicked()), this, SLOT(on_black_clicked()));
    x_black->setFixedSize(20, 20);
    x_black->setStyleSheet("background-color:rgb(0,0,0);");
    x_white = new XLabel(NULL);
    connect(x_white, SIGNAL(clicked()), this, SLOT(on_white_clicked()));
    x_white->setFixedSize(20, 20);
    x_white->setStyleSheet("background-color:rgb(255,255,255);");
    x_yellow = new XLabel(NULL);
    connect(x_yellow, SIGNAL(clicked()), this, SLOT(on_yellow_clicked()));
    x_yellow->setFixedSize(20, 20);
    x_yellow->setStyleSheet("background-color:rgb(255,255,0);");
    x_lightgreen = new XLabel(NULL);
    connect(x_lightgreen, SIGNAL(clicked()), this, SLOT(on_lightgreen_clicked()));
    x_lightgreen->setFixedSize(20, 20);
    x_lightgreen->setStyleSheet("background-color:rgb(0,255,0);");
    x_lightblue = new XLabel(NULL);
    connect(x_lightblue, SIGNAL(clicked()), this, SLOT(on_lightblue_clicked()));
    x_lightblue->setFixedSize(20, 20);
    x_lightblue->setStyleSheet("background-color:rgb(0,128,255);");

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

void PaintToolBar::on_roaming_clicked()
{

}

void PaintToolBar::on_select_clicked()
{

}


void PaintToolBar::on_fullsave_clicked()
{

}


void PaintToolBar::on_localsave_clicked()
{

}


void PaintToolBar::on_fullclear_clicked()
{

}


void PaintToolBar::on_localclear_clicked()
{

}


void PaintToolBar::on_revocation_clicked()
{

}


void PaintToolBar::on_brush_clicked()
{

}


void PaintToolBar::on_spoint_clicked()
{

}


void PaintToolBar::on_mpoint_clicked()
{

}


void PaintToolBar::on_bpoint_clicked()
{

}


void PaintToolBar::on_red_clicked()
{

}


void PaintToolBar::on_darkblue_clicked()
{

}


void PaintToolBar::on_darkgreen_clicked()
{

}


void PaintToolBar::on_orange_clicked()
{

}


void PaintToolBar::on_black_clicked()
{

}


void PaintToolBar::on_white_clicked()
{

}


void PaintToolBar::on_yellow_clicked()
{

}


void PaintToolBar::on_lightgreen_clicked()
{

}


void PaintToolBar::on_lightblue_clicked()
{

}

