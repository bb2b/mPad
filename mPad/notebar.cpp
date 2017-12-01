#include "notebar.h"
#include "ui_notebar.h"
#include "global.h"

NoteBar::NoteBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteBar)
{
    ui->setupUi(this);
    ui->NoteButton->setFixedSize(100, 60);
    ui->NotePanel->hide();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 120, GetSystemMetrics(SM_CYSCREEN) - 120, 100, 60);
}

NoteBar::~NoteBar()
{
    delete ui;
}

void NoteBar::on_NoteButton_clicked()
{
    ui->NotePanel->show();
}

void NoteBar::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().y() > this->height() - 60)
    {
        b_move = true;
        m_last_point = event->pos();
    }
}

void NoteBar::mouseMoveEvent(QMouseEvent *event)
{
    if (b_move)
        this->move(this->pos() + event->pos() - m_last_point);
}

void NoteBar::mouseReleaseEvent(QMouseEvent *event)
{
    b_move = false;
}
