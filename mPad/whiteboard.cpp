#include "whiteboard.h"
#include "global.h"
#include <QPolygonF>
#include <QPainterPath>

WhiteBoard::WhiteBoard(QWidget *parent) : QWidget(parent)
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

void WhiteBoard::prepare(bool isTransparent)
{
    m_image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
    if(isTransparent)
    {
        QPixmap pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), 0, 0, this->width(), this->height());
        QPalette pal(palette());
        pal.setBrush(QPalette::Background, QBrush(pixmap));
        setPalette(pal);
        m_image.fill(QColor(0, 0, 0, 0));
    }
    else
    {
        //this->setAttribute(Qt::WA_TranslucentBackground, false);
        m_image.fill(QColor(0, 170, 127));
    }
    m_image_temp = m_image;
    m_current_image = &m_image_temp;
    pointsThis.clear();
}

void WhiteBoard::paint()
{
    if(!m_pressed)
    {
        if(g_draw_type == ERASE)
        {
            m_current_image = &m_image_temp;
            QPolygonF polygon(pointsTemp);
            QPainterPath painterpath;
            painterpath.addPolygon(polygon);
            QPainter painter;
            painter.begin(m_current_image);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillPath(painterpath, QColor(0, 0, 0, 0));
            painter.end();
            return;
        }
        else if(g_draw_type == SELECT)
        {
            m_current_image = &m_image_temp;
        }
    }

    if(g_draw_type == ROAMING)
    {
        m_image_temp = m_image;
        m_current_image = &m_image_temp;
        for(int i = 0; i < pointsThis.size(); i++)
        {
            for(int j = 0; j < pointsThis.at(i).points.size(); j++)
            {
                pointsThis[i].points[j] += m_end_point;
                pointsThis[i].points[j] -= m_move_start_point;
            }
            if(pointsThis.at(i).erase)
            {
                QPolygonF polygon(pointsThis.at(i).points);
                QPainterPath painterpath;
                painterpath.addPolygon(polygon);
                QPainter painter;
                painter.begin(m_current_image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setCompositionMode(QPainter::CompositionMode_Source);
                painter.fillPath(painterpath, QColor(0, 0, 0, 0));
                painter.end();
            }
            else
            {
                QPen pen;
                pen.setColor(pointsThis.at(i).color);
                pen.setWidth(pointsThis.at(i).width);
                QPolygonF polygon(pointsThis.at(i).points);
                QPainterPath painterpath;
                painterpath.addPolygon(polygon);
                QPainter painter;
                painter.begin(m_current_image);
                painter.setPen(pen);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setCompositionMode(QPainter::CompositionMode_Source);
                painter.drawPath(painterpath);
                painter.end();
            }
        }
        return;
    }

    QPen pen;
    if(g_draw_type == ERASE)
        pen.setColor(LOCALCLEAR_COLOR);
    else if(g_draw_type == SELECT)
        pen.setColor(SELECT_COLOR);
    else
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

void WhiteBoard::revocation()
{
    if(pointsThis.isEmpty()) return;
    m_image_temp = m_image;
    m_current_image = &m_image_temp;
    for(int i = 0; i < pointsThis.size() - 1; i++)
    {
        if(pointsThis.at(i).erase)
        {
            QPolygonF polygon(pointsThis.at(i).points);
            QPainterPath painterpath;
            painterpath.addPolygon(polygon);
            QPainter painter;
            painter.begin(m_current_image);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillPath(painterpath, QColor(0, 0, 0, 0));
            painter.end();
        }
        else
        {
            QPen pen;
            pen.setColor(pointsThis.at(i).color);
            pen.setWidth(pointsThis.at(i).width);
            QPolygonF polygon(pointsThis.at(i).points);
            QPainterPath painterpath;
            painterpath.addPolygon(polygon);
            QPainter painter;
            painter.begin(m_current_image);
            painter.setPen(pen);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawPath(painterpath);
            painter.end();
        }
    }
    update();
    pointsThis.pop_back();
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
    m_move_start_point = event->pos();
    if(g_draw_type == ERASE || g_draw_type == SELECT)
    {
        m_image_temp_2 = m_image_temp;
        m_current_image = &m_image_temp_2;
    }
    if(g_draw_type == ROAMING)
    {
        setCursor(Qt::SizeAllCursor);
    }
    else
        pointsTemp.clear();
}

void WhiteBoard::mouseMoveEvent(QMouseEvent *event)
{
    m_end_point = event->pos();
    paint();
    if(g_draw_type != ROAMING)
        pointsTemp.push_back(m_move_start_point);
    static int count = 0;
    if (count++ % 3 == 0) update();
    m_move_start_point = event->pos();
}

void WhiteBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(g_draw_type == ROAMING)
    {
        setCursor(Qt::ArrowCursor);
    }
    else
        pointsTemp.push_back(m_move_start_point);
    m_pressed = false;
    m_end_point = event->pos();
    paint();
    update();
    if(g_draw_type != SELECT || g_draw_type != ROAMING)
    {
        Points points_temp;
        if(g_draw_type == DRAW)
            points_temp.erase = false;
        else
            points_temp.erase = true;
        points_temp.color = g_draw_color;
        points_temp.width = g_draw_width;
        points_temp.points = pointsTemp;
        pointsThis.push_back(points_temp);
    }
}
