#include "file.h"
#include "global.h"

File::File(bool islarge, QString filepath, QString filename, QString filecreatetime, QString filedescription, int filesize, QWidget *parent) : QLabel(parent)
{
    isLargeDisplay = islarge;
    filePath = filepath;
    fileName = filename;
    fileCreateTime = filecreatetime;
    fileDescription = filedescription;
    fileSize = filesize;

    if(isLargeDisplay)
    {
        m_large_file_name = new QLabel(this);
        m_large_file_name->setText(filename);
    }
    else
    {
        m_tiny_bg = new QLabel(this);
        m_tiny_file_name = new QLabel(m_tiny_bg);
        m_tiny_file_name->setText(filename);
        m_tiny_file_description = new QLabel(m_tiny_bg);
        m_tiny_file_description->setText(filedescription);
        m_tiny_file_size = new QLabel(m_tiny_bg);
        m_tiny_file_size->setText(QString::number(filesize) + "KB");
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
        this->setStyleSheet("QLabel{border-left-width: 25px; border-right-width: 25px; border-top-width: 5px; border-bottom-width: 25px; border-style: solid; border-color: transparent;}");
        this->setPixmap(QPixmap(":/res/file.png"));
        m_large_file_name->setGeometry(0, h - 25, w, 25);
    }
    else
    {
        this->setStyleSheet("QLabel{border-left-width: 5px; border-right-width: 50px; border-top-width: 5px; border-bottom-width: 5px; border-style: solid; border-color: transparent;}");
        this->setPixmap(QPixmap(":/res/file.png"));
        m_tiny_bg->setGeometry(w - 50, 0, 50, h);
        m_tiny_file_name->setGeometry(0, 0, m_tiny_bg->width(), m_tiny_bg->height() / 2);
        m_tiny_file_description->setGeometry(0, m_tiny_bg->height() / 2, m_tiny_bg->width(), m_tiny_bg->height() / 4);
        m_tiny_file_size->setGeometry(0, m_tiny_bg->height() * 3 / 4, m_tiny_bg->width(), m_tiny_bg->height() / 4);
    }
}

