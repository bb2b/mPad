#include "screenshot.h"
#include "global.h"

ScreenShot::ScreenShot(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setGeometry(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    m_close = new QPushButton(this);
    m_close->setText("关闭");
    connect(m_close, SIGNAL(clicked()), this, SLOT(on_close_button_clicked()));
    m_ok = new QPushButton(this);
    m_ok->setText("保存");
    connect(m_ok, SIGNAL(clicked()), this, SLOT(on_ok_button_clicked()));
    m_zoomin = new QPushButton(this);
    m_zoomin->setText("放大");
    connect(m_zoomin, SIGNAL(clicked()), this, SLOT(on_zoomin_button_clicked()));
}

ScreenShot::~ScreenShot()
{
    delete m_close;
    delete m_ok;
    delete m_zoomin;
}

void ScreenShot::prepare()
{
    pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), 0, 0, this->width(), this->height());
    QPalette pal(palette());
    pal.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(pal);
    m_image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
    m_image.fill(QColor(0, 0, 128, 32));

    m_image_temp = m_image;
    m_image_current = &m_image_temp;

    m_disable_event = false;

    m_close->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 70, 10, 60, 30);
    m_ok->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 70, 10, 60, 30);
    m_zoomin->setGeometry(GetSystemMetrics(SM_CXSCREEN) - 70, 10, 60, 30);
    m_ok->setVisible(false);
    m_zoomin->setVisible(false);
}

void ScreenShot::paint()
{
    if (m_pressed) {
        m_image_temp = m_image;
        m_image_current = &m_image_temp;
    } else {
        m_image_current = &m_image;
    }
    QPen pen;
    pen.setColor(QColor(0,162,232));
    pen.setWidth(2);
    QPainter painter;
    painter.begin(m_image_current);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    if (!m_pressed)
        painter.fillRect(QRect(m_start_point, m_end_point), QColor(0, 0, 0, 0));
    painter.drawRect(QRect(m_start_point, m_end_point));
    painter.end();
}

void ScreenShot::on_close_button_clicked()
{
    hide();
}

void ScreenShot::on_ok_button_clicked()
{
    QString savepath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    savepath += generate_name_by_current_time();
    QPixmap pixmap_temp = QPixmap::fromImage(m_image_screenshot);
    pixmap_temp.save(savepath, "JPG", 100);
    hide();
}

void ScreenShot::on_zoomin_button_clicked()
{
    m_image_current = &m_image;
    QPen pen;
    pen.setColor(QColor(0,162,232));
    pen.setWidth(2);
    QPainter painter;
    painter.begin(m_image_current);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawRect(QRect(QPoint(50, 50), QPoint(this->width() - 50, this->height() - 50)));
    painter.drawImage(QRect(QPoint(51, 51), QPoint(this->width() - 51, this->height() - 51)), m_image_screenshot);
    painter.end();

    m_zoomin->move(50, 10);
    m_close->move(130, 10);
    m_ok->move(210, 10);

    update();
}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *m_image_current);
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    if(m_disable_event) return;

    m_pressed = true;

    m_start_point = event->pos();
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    if(m_disable_event) return;

    m_end_point = event->pos();
    paint();

    static int count = 0;
    if (count++ % 3 == 0) update();
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_disable_event) return;

    m_pressed = false;

    m_end_point = event->pos();
    if(m_start_point == m_end_point) return;
    paint();
    update();

    m_zoomin->move(m_start_point.y() < m_end_point.y() ? QPoint(m_start_point.x(), m_start_point.y() - 40) : QPoint(m_end_point.x(), m_end_point.y() - 40));
    m_close->move(m_start_point.y() < m_end_point.y() ? QPoint(m_start_point.x() + 80, m_start_point.y() - 40) : QPoint(m_end_point.x() + 80, m_end_point.y() - 40));
    m_ok->move(m_start_point.y() < m_end_point.y() ? QPoint(m_start_point.x() + 160, m_start_point.y() - 40) : QPoint(m_end_point.x() + 160, m_end_point.y() - 40));
    m_zoomin->setVisible(true);
    m_ok->setVisible(true);

    m_disable_event = true;

    m_image_screenshot = pixmap.toImage().copy(QRect(m_start_point, m_end_point));
}
