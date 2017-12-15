#include <QFileIconProvider>
#include <QFileInfo>
#include "file.h"
#include "global.h"

File::File(bool islarge, QString filepath, QString filename, QWidget *parent) : QLabel(parent)
{
    isLargeDisplay = islarge;
    filePath = filepath;
    fileName = filename;

    m_icon = new QLabel(this);
    m_icon->setScaledContents(true);

    if(isLargeDisplay)
    {
        m_large_file_name = new QLabel(this);
        m_large_file_name->setAlignment(Qt::AlignCenter);
        m_large_file_name->setText(filename);
    }
    else
    {
        m_tiny_bg = new QLabel(this);
        m_tiny_file_name = new QLabel(m_tiny_bg);
        m_tiny_file_name->setText(filename);
        QString file_description = "";
        SHFILEINFOA info;
        if(SHGetFileInfoA(QString(filePath + "\\" + fileName).toStdString().c_str(),
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
        QFileInfo fileinfo(filePath + "\\" + fileName);
        m_tiny_file_size = new QLabel(m_tiny_bg);
        m_tiny_file_size->setText(QString::number(fileinfo.size()) + "KB");
    }
}

File::~File()
{
    if(isLargeDisplay)
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

void File::mousePressEvent(QMouseEvent *event)
{

}

void File::mouseReleaseEvent(QMouseEvent *event)
{

}

void File::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
    if(isLargeDisplay)
    {
        //this->setStyleSheet("QLabel{border-left-width: 40px; border-right-width: 40px; border-top-width: 5px; border-bottom-width: 40px; border-style: solid; border-color: transparent;}");
        m_icon->setGeometry(0, 0, w, h - 40);
        m_icon->setPixmap(fileIcon(filePath + "\\" + fileName).pixmap(w, h));
        m_large_file_name->setGeometry(0, h - 40, w, 40);
    }
    else
    {
        this->setStyleSheet("QLabel{border-left-width: 5px; border-right-width: 50px; border-top-width: 5px; border-bottom-width: 5px; border-style: solid; border-color: transparent;}");
        this->setPixmap(fileIcon(filePath + "\\" + fileName).pixmap(w, h));
        m_tiny_bg->setGeometry(w - 50, 0, 50, h);
        m_tiny_file_name->setGeometry(0, 0, m_tiny_bg->width(), m_tiny_bg->height() / 2);
        m_tiny_file_description->setGeometry(0, m_tiny_bg->height() / 2, m_tiny_bg->width(), m_tiny_bg->height() / 4);
        m_tiny_file_size->setGeometry(0, m_tiny_bg->height() * 3 / 4, m_tiny_bg->width(), m_tiny_bg->height() / 4);
    }
}

