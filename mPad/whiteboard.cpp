#include "whiteboard.h"
#include "ui_whiteboard.h"
#include "global.h"

WhiteBoard::WhiteBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WhiteBoard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(0, -GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

WhiteBoard::~WhiteBoard()
{
    delete ui;
}
