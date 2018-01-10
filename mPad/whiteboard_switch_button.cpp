#include "whiteboard_switch_button.h"
#include "global.h"

SwitchBoard::SwitchBoard(QWidget *parent) :
    QWidget(parent)
  , b_move_direction(true)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry((GetSystemMetrics(SM_CXSCREEN) - 75) / 2, 0, 75, 23);
    this->setStyleSheet("background-color:rgb(134,134,134);");

    vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);

    pushButton = new QPushButton(this);
    pushButton->setText("下拉");
    connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    vLayout->addWidget(pushButton);
    this->setLayout(vLayout);

    connect(&move_timer, SIGNAL(timeout()), this, SLOT(on_move_timer_out()));
}

SwitchBoard::~SwitchBoard()
{
    delete pushButton;
    delete vLayout;
}

void SwitchBoard::on_pushButton_clicked()
{
    set_window_top_hint(g_whiteboard, HWND_TOP, true);
    if(b_move_direction)
        g_whiteboard->move(0, -g_whiteboard->height());
    g_whiteboard->prepare(false);
    if(!move_timer.isActive())
        move_timer.start(1);
}

void SwitchBoard::on_move_timer_out()
{
    if(b_move_direction)
    {
        if(g_whiteboard->pos().y() < 0)
        {
            g_whiteboard->move(0, g_whiteboard->pos().y() + 2);
            if(this->pos().y() < GetSystemMetrics(SM_CYSCREEN) - 23)
                this->move(this->pos().x(), this->pos().y() + 2);
        }
        else
        {
            b_move_direction = false;
            move_timer.stop();
            g_notebar->on_painttoolbar(false);
            g_desktopswitchbar->hide();
            pushButton->setText("上拉");
            return;
        }
    }
    else
    {
        if(g_whiteboard->pos().y() + g_whiteboard->height() > 0)
        {
            g_whiteboard->move(0, g_whiteboard->pos().y() - 2);
            if(this->pos().y() >= 0)
                this->move(this->pos().x(), this->pos().y() - 2);
        }
        else
        {
            b_move_direction = true;
            move_timer.stop();
            g_notebar->on_painttoolbar(true);
            g_desktopswitchbar->show();
            pushButton->setText("下拉");
            return;
        }
    }
}
