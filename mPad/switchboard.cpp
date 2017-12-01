#include "switchboard.h"
#include "ui_switchboard.h"
#include "global.h"

SwitchBoard::SwitchBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SwitchBoard)
  , b_move_direction(true)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry((GetSystemMetrics(SM_CXSCREEN) - 75) / 2, 0, 75, 23);

    connect(&move_timer, SIGNAL(timeout()), this, SLOT(on_move_timer_out()));
}

SwitchBoard::~SwitchBoard()
{
    delete ui;
}

void SwitchBoard::on_pushButton_clicked()
{
    set_window_top_hint(g_whiteboard, HWND_TOP, true);
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
            return;
        }
    }
}
