#include <QFileIconProvider>
#include <QFileInfo>
#include "file.h"
#include "global.h"

File::File(bool on_window_or_pupup, QFileInfo fileinfo, QWidget *parent) : QLabel(parent),
    b_on_window_or_pupup(on_window_or_pupup),
    m_fileinfo(fileinfo)
{
    setCursor(Qt::PointingHandCursor);

    m_icon = new QLabel(this);
    m_icon->setScaledContents(true);

    if(b_on_window_or_pupup)
    {
        m_large_file_name = new QLabel(this);
        m_large_file_name->setAlignment(Qt::AlignCenter);
        m_large_file_name->setText(m_fileinfo.fileName());
    }
    else
    {
        m_tiny_bg = new QLabel(this);
        m_tiny_file_name = new QLabel(m_tiny_bg);
        m_tiny_file_name->setText(m_fileinfo.fileName());
        QString file_description = "";
        SHFILEINFOA info;
        if(SHGetFileInfoA(fileinfo.absoluteFilePath().toStdString().c_str(),
         FILE_ATTRIBUTE_NORMAL,
         &info,
         sizeof(info),
         SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES))
        {
            std::string type = info.szTypeName;
            file_description = type.c_str();
        }
        m_tiny_file_description = new QLabel(m_tiny_bg);
        m_tiny_file_description->setText(file_description);
        m_tiny_file_size = new QLabel(m_tiny_bg);
        m_tiny_file_size->setText(QString::number(m_fileinfo.size()) + "KB");
    }
}

File::~File()
{
    if(b_on_window_or_pupup)
    {
        delete m_large_file_name;
    }
    else
    {
        delete m_tiny_file_name;
        delete m_tiny_file_description;
        delete m_tiny_file_size;
        delete m_tiny_bg;
    }
}

QIcon File::fileIcon(const QString filepath)
{
    QFileIconProvider provider;
    return provider.icon(QFileInfo(filepath));
}

void File::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&\
            event->pos().x() >= 0 &&\
            event->pos().x() <= this->width() &&\
            event->pos().y() >= 0 &&\
            event->pos().y() <= this->height())
    {
        emit clicked();
    }
}

void File::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
    if(isLargeDisplay)
    {
        //this->setStyleSheet("QLabel{border-left-width: 40px; border-right-width: 40px; border-top-width: 5px; border-bottom-width: 40px; border-style: solid; border-color: transparent;}");
        m_icon->setGeometry(0, 0, w, h - 40);
        m_icon->setPixmap(fileIcon(m_fileinfo.absoluteFilePath()).pixmap(w, h));
        m_large_file_name->setGeometry(0, h - 40, w, 40);
    }
    else
    {
        this->setStyleSheet("QLabel{border-left-width: 5px; border-right-width: 50px; border-top-width: 5px; border-bottom-width: 5px; border-style: solid; border-color: transparent;}");
        this->setPixmap(fileIcon(m_fileinfo.absoluteFilePath()).pixmap(w, h));
        m_tiny_bg->setGeometry(w - 50, 0, 50, h);
        m_tiny_file_name->setGeometry(0, 0, m_tiny_bg->width(), m_tiny_bg->height() / 2);
        m_tiny_file_description->setGeometry(0, m_tiny_bg->height() / 2, m_tiny_bg->width(), m_tiny_bg->height() / 4);
        m_tiny_file_size->setGeometry(0, m_tiny_bg->height() * 3 / 4, m_tiny_bg->width(), m_tiny_bg->height() / 4);
    }
}

