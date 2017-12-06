#include "whiteboard.h"
#include "global.h"
#include <QPixmap>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>

WhiteBoard::WhiteBoard()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setGeometry(0, -GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    //QPalette pal(palette());
    //pal.setColor(QPalette::Background, QColor(0,0,0,0));
    //setAutoFillBackground(true);
    //setPalette(pal);
    //this->setStyleSheet("QLabel{background-color:rgba(0,0,0,0%);}");
}

WhiteBoard::~WhiteBoard()
{
}

void WhiteBoard::prepare(bool istransparent)
{
    m_image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
    if(istransparent)
    {
        QPixmap pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), 0, 0, this->width(), this->height());
        QPalette pal(palette());
        pal.setBrush(QPalette::Background, QBrush(pixmap));
        setPalette(pal);
        m_image.fill(QColor(0, 0, 0, 1));
    }
    else
    {
        //this->setAttribute(Qt::WA_TranslucentBackground, false);
        m_image.fill(QColor(0, 170, 127));
    }
    m_image_temp = m_image;
    m_current_image = &m_image_temp;
}

void WhiteBoard::paint()
{
    QPen pen;
    pen.setColor(g_draw_color);
    pen.setWidth(g_draw_width);
    QPainter painter;
    painter.begin(m_current_image);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawLine(QLine(m_move_start_point, m_end_point));
    painter.end();
}

void WhiteBoard::fullclear()
{
    m_image_temp = m_image;
    m_current_image = &m_image_temp;
    update();
}

void WhiteBoard::localclear()
{
    g_draw_color = QColor(0,0,0,0);
}

void WhiteBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *m_current_image);
}

void WhiteBoard::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;

    m_start_point = event->pos();
    m_end_point = NULL_POINT;
    m_move_start_point = event->pos();
}

void WhiteBoard::mouseMoveEvent(QMouseEvent *event)
{
    m_end_point = event->pos();
    paint();

    static int count = 0;
    if (count++ % 2 == 0)
        update();

    m_move_start_point = event->pos();
}

void WhiteBoard::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    m_end_point = event->pos();
    paint();
    update();
}
