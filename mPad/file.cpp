#include <QFileIconProvider>
#include <QFileInfo>
#include <QProcess>
#include <QAxWidget>
#include <QAxObject>
#include "file.h"
#include "global.h"
#include "explorerwindow.h"

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
            file_description = QString::fromLocal8Bit(type.c_str());
        }
        QFont font("宋体", 7, QFont::Normal);
        m_tiny_file_description = new QLabel(m_tiny_bg);
        m_tiny_file_description->setText(file_description);
        m_tiny_file_description->setFont(font);
        m_tiny_file_size = new QLabel(m_tiny_bg);
        m_tiny_file_size->setText(QString::number(m_fileinfo.size()) + "B");
        m_tiny_file_size->setFont(font);
    }

    tempPDF_dir = qApp->applicationDirPath().replace("/", "\\") + "\\TempPDF\\";
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

QIcon File::fileIcon()
{
    QFileIconProvider provider;
    return provider.icon(m_fileinfo);
}

void File::openExcel()
{
    if(!ExplorerWindow::g_files.contains(m_fileinfo.absoluteFilePath()))
    {
        QAxObject *excelContent = new QAxObject("Excel.Application", 0);
        QAxObject *workbookObj = excelContent->querySubObject("Workbooks");
        QAxObject *workbook = workbookObj->querySubObject("Open(QString)", m_fileinfo.absoluteFilePath().replace("/", "\\"));
        QDir temp_dir(tempPDF_dir);
        if(!temp_dir.exists())
            temp_dir.mkpath(tempPDF_dir);
        QString pdf_store_file_path = tempPDF_dir + m_fileinfo.fileName() + "." + m_fileinfo.lastModified().toString("yyyyMMddhhmmsszzz") + ".pdf";;
        workbook->dynamicCall("ExportAsFixedFormat(int,QString)",0, pdf_store_file_path);
        workbook->dynamicCall("Close()");
        workbookObj->dynamicCall("Close()");
        excelContent->dynamicCall("Quit()");
        delete workbook;
        delete workbookObj;
        delete excelContent;
        openPdf(pdf_store_file_path);
    }
}

void File::openPpt()
{
    if(!ExplorerWindow::g_files.contains(m_fileinfo.absoluteFilePath()))
    {
        QAxObject *pptContent = new QAxObject("Powerpoint.Application", /*explorerwindow*/0);
        QAxObject *presentationObj = pptContent->querySubObject("Presentations");
        QAxObject *presentation = presentationObj->querySubObject("Open(QString,int,int,int)", m_fileinfo.absoluteFilePath().replace("/", "\\"),0,0,0);
        QDir temp_dir(tempPDF_dir);
        if(!temp_dir.exists())
            temp_dir.mkpath(tempPDF_dir);
        QString pdf_store_file_path = tempPDF_dir + m_fileinfo.fileName() + "." + m_fileinfo.lastModified().toString("yyyyMMddhhmmsszzz") + ".pdf";;
        presentation->dynamicCall("SaveAs(QString,int,int)", pdf_store_file_path,32,0);
        presentation->dynamicCall("Close()");
        //presentationObj->dynamicCall("Close()");
        pptContent->dynamicCall("Quit()");
        delete presentation;
        delete presentationObj;
        delete pptContent;
        openPdf(pdf_store_file_path);
    }
}

void File::openWord()
{
    if(!ExplorerWindow::g_files.contains(m_fileinfo.absoluteFilePath()))
    {
        QAxObject *excelContent = new QAxObject("Word.Application", 0);
        QAxObject *documentObj = excelContent->querySubObject("Documents");
        QAxObject *document = documentObj->querySubObject("Open(QString)", m_fileinfo.absoluteFilePath().replace("/", "\\"));
        QDir temp_dir(tempPDF_dir);
        if(!temp_dir.exists())
            temp_dir.mkpath(tempPDF_dir);
        QString pdf_store_file_path = tempPDF_dir + m_fileinfo.fileName() + "." + m_fileinfo.lastModified().toString("yyyyMMddhhmmsszzz") + ".pdf";
        document->dynamicCall("ExportAsFixedFormat(QString,int)", pdf_store_file_path,17);
        //document->dynamicCall("Close()");
        //documentObj->dynamicCall("Close()");
        excelContent->dynamicCall("Quit()");
        delete document;
        delete documentObj;
        delete excelContent;
        openPdf(pdf_store_file_path);
    }
}

void File::openPdf(QString filepath)
{
    if(!ExplorerWindow::g_files.contains(filepath))
    {
        ExplorerWindow *explorerwindow = new ExplorerWindow(filepath, g_mainwindow);
        //explorerwindow->setGeometry(GetSystemMetrics(SM_CXSCREEN)/4,GetSystemMetrics(SM_CYSCREEN)/4,GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2);
        explorerwindow->show();
    }
}

void File::openPic()
{

}

void File::openVideo()
{

}

void File::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&\
            event->pos().x() >= 0 &&\
            event->pos().x() <= this->width() &&\
            event->pos().y() >= 0 &&\
            event->pos().y() <= this->height())
    {
        if(m_fileinfo.isFile())
        {
            if(m_fileinfo.suffix() == "docx" || m_fileinfo.suffix() == "doc")
            {
                openWord();
            }
            else if(m_fileinfo.suffix() == "xlsx" || m_fileinfo.suffix() == "xls")
            {
                openExcel();
            }
            else if(m_fileinfo.suffix() == "pptx" || m_fileinfo.suffix() == "ppt")
            {
                openPpt();
            }
            else if(m_fileinfo.suffix() == "pdf")
            {
                openPdf(m_fileinfo.absoluteFilePath());
            }
            else if(m_fileinfo.suffix() == "bmp" || m_fileinfo.suffix() == "gif" || m_fileinfo.suffix() == "jpe" || m_fileinfo.suffix() == "jpeg" || m_fileinfo.suffix() == "jpg" || m_fileinfo.suffix() == "png")
            {
                openPic();
            }
            else if(m_fileinfo.suffix() == "mp4" || m_fileinfo.suffix() == "avi" || m_fileinfo.suffix() == "mov" || m_fileinfo.suffix() == "wmv")
            {
                openVideo();
            }
            else
            {
                QString tempStr = m_fileinfo.absoluteFilePath().replace("/", "\\");
                QProcess::execute("explorer " + tempStr);
            }
        }
        else
            emit clicked();
    }
}

void File::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
    if(b_on_window_or_pupup)
    {
        //this->setStyleSheet("QLabel{border-left-width: 40px; border-right-width: 40px; border-top-width: 5px; border-bottom-width: 40px; border-style: solid; border-color: transparent;}");
        m_icon->setGeometry(0, 0, w, h - 40);
        m_icon->setPixmap(fileIcon().pixmap(w, h));
        m_large_file_name->setGeometry(0, h - 40, w, 40);
    }
    else
    {
        //this->setStyleSheet("QLabel{border-left-width: 5px; border-right-width: 50px; border-top-width: 5px; border-bottom-width: 5px; border-style: solid; border-color: transparent;}");
        //this->setPixmap(fileIcon(m_fileinfo.absoluteFilePath()).pixmap(w, h));
        m_icon->setGeometry(0, h / 2 - w / 12, w / 6, w / 6);
        m_icon->setPixmap(fileIcon().pixmap(m_icon->width(), m_icon->height()));
        m_tiny_bg->setGeometry(w / 6, 0, w - w / 6, h);
        m_tiny_file_name->setGeometry(0, 0, m_tiny_bg->width(), m_tiny_bg->height() / 2);
        m_tiny_file_description->setGeometry(0, m_tiny_bg->height() / 2, m_tiny_bg->width(), m_tiny_bg->height() / 4);
        m_tiny_file_size->setGeometry(0, m_tiny_bg->height() * 3 / 4, m_tiny_bg->width(), m_tiny_bg->height() / 4);
    }
}

