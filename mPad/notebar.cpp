#include "notebar.h"
#include "ui_notebar.h"

NoteBar::NoteBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteBar)
{
    ui->setupUi(this);
}

NoteBar::~NoteBar()
{
    delete ui;
}
