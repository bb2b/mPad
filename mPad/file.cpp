#include "file.h"
#include "global.h"

File::File(bool islarge, QString filepath, QString filename, QString filecreatetime, QString filedescription, int filesize, QWidget *parent) : QLabel(parent)
{
    if(islarge)
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

    isLargeDisplay = islarge;
    filePath = filepath;
    fileName = filename;
    fileCreateTime = filecreatetime;
    fileDescription = filedescription;
    fileSize = filesize;
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
    }
    else
    {
        this->setStyleSheet("QLabel{border-left-width: 5px; border-right-width: 25px; border-top-width: 5px; border-bottom-width: 25px; border-style: solid; border-color: transparent;}");
        this->setPixmap(QPixmap(":/res/file.png"));
    }
}

