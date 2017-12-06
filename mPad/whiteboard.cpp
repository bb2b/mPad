#include "whiteboard.h"
#include "global.h"
#include <QPixmap>
#include <QScreen>
#include <QDesktopWidget>

WhiteBoard::WhiteBoard()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(0, -GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
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
        QPalette pal(this->palette());
        pal.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(pal);
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        m_image.fill(QColor(0, 0, 128, 32));
    }
    else
    {
        //this->setAttribute(Qt::WA_TranslucentBackground, false);
        m_image.fill(QColor(0, 170, 127));
    }
    m_current_image = &m_image;
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
    painter.drawLine(QLine(m_move_start_point, m_end_point));
    painter.end();
}

void WhiteBoard::fullclear()
{
    prepare(true);
    update();
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
