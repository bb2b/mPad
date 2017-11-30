#include "switchboard.h"
#include "ui_switchboard.h"

SwitchBoard::SwitchBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SwitchBoard)
{
    ui->setupUi(this);
}

SwitchBoard::~SwitchBoard()
{
    delete ui;
}
