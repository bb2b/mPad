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

void WhiteBoard::prepare(bool istransparent)
{
    m_image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
    if(istransparent)
    {
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        m_image.fill(QColor(0, 170, 127));
    }
    else
    {
        this->setAttribute(Qt::WA_TranslucentBackground, false);
        m_image.fill(QColor(0, 170, 127));
    }
    m_current_image = &m_image;
}

void WhiteBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *m_current_image);
}
