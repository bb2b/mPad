#include "whiteboard.h"
#include "ui_whiteboard.h"

WhiteBoard::WhiteBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WhiteBoard)
{
    ui->setupUi(this);
}

WhiteBoard::~WhiteBoard()
{
    delete ui;
}
