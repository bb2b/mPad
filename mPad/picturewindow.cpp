#include "picturewindow.h"
#include "global.h"

QVector<QString> PictureWindow::g_pictures(0);

PictureWindow::PictureWindow(QString picpath, QWidget *parent) : QDialog(parent),
    m_picpath(picpath)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);

    PictureWindow::g_pictures.push_back(m_picpath);
    m_display = new QLabel(this);
    m_close_btn = new QPushButton(m_display);
    m_close_btn->setText("关闭");

    connect(m_close_btn, SIGNAL(clicked()), this, SLOT(on_close_btn_clicked()));

    m_pixmap = new QPixmap(m_picpath);

    if(m_pixmap == NULL || m_pixmap->isNull())
    {
        this->close();
        return;
    }

    int h = GetSystemMetrics(SM_CYSCREEN) / 2;
    int w = m_pixmap->width() * h / m_pixmap->height();
    setGeometry((GetSystemMetrics(SM_CXSCREEN) - w)/2, (GetSystemMetrics(SM_CYSCREEN) - h)/2, w, h);
}

PictureWindow::~PictureWindow()
{
    delete m_close_btn;
    delete m_display;
    delete m_pixmap;
}

void PictureWindow::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
}

void PictureWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    int h = GetSystemMetrics(SM_CYSCREEN);
    int w = m_pixmap->width() * h / m_pixmap->height();
    this->setGeometry((GetSystemMetrics(SM_CXSCREEN) - w)/2, (GetSystemMetrics(SM_CYSCREEN) - h)/2, w, h);
}

void PictureWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint new_point = this->pos() + event->pos() - m_last_point;
    if(b_move && new_point.x() >= 0 && new_point.x() + this->width() <= GetSystemMetrics(SM_CXSCREEN) && new_point.y() >= 0 && new_point.y() + this->height() <= GetSystemMetrics(SM_CYSCREEN))
    {
        this->move(new_point);
    }
    else
        m_last_point = event->pos();
}

void PictureWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    b_move = false;
}

void PictureWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    m_close_btn->setGeometry(w-45,h-20,40,20);
    m_display->setGeometry(0,0,w,h);
    m_display->setPixmap(m_pixmap->scaled(w, h));
}

void PictureWindow::on_close_btn_clicked()
{
    PictureWindow::g_pictures.removeOne(m_picpath);
    this->close();
}
