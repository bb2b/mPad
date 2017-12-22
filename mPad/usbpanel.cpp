#include "usbpanel.h"
#include "global.h"

UsbPanel::UsbPanel(QString UsbName, QWidget *parent) : QWidget(parent),
    m_usbname(UsbName),
    filemanagewindow_all(NULL),
    filemanagewindow_note(NULL),
    filemanagewindow_pic(NULL),
    filemanagepopup_ppt(NULL),
    filemanagepopup_word(NULL),
    filemanagepopup_excel(NULL),
    filemanagepopup_pdf(NULL),
    filemanagepopup_movie(NULL),
    filemanagepopup_other(NULL)
{
    this->setStyleSheet("background-color:rgb(188,188,188);");

    m_usb_all = new myLabel(this);
    m_usb_all->setText("USB");
    connect(m_usb_all, SIGNAL(clicked()), this, SLOT(on_usb_all_clicked()));
    m_note_files = new myLabel(this);
    m_note_files->setText("批注文件");
    connect(m_note_files, SIGNAL(clicked()), this, SLOT(on_note_files_clicked()));
    m_ppt_files = new myLabel(this);
    m_ppt_files->setText("ppt文件");
    connect(m_ppt_files, SIGNAL(clicked()), this, SLOT(on_ppt_files_clicked()));
    m_word_files = new myLabel(this);
    m_word_files->setText("word文件");
    connect(m_word_files, SIGNAL(clicked()), this, SLOT(on_word_files_clicked()));
    m_excel_files = new myLabel(this);
    m_excel_files->setText("excel文件");
    connect(m_excel_files, SIGNAL(clicked()), this, SLOT(on_excel_files_clicked()));
    m_pdf_files = new myLabel(this);
    m_pdf_files->setText("pdf文件");
    connect(m_pdf_files, SIGNAL(clicked()), this, SLOT(on_pdf_files_clicked()));
    m_picture_files = new myLabel(this);
    m_picture_files->setText("图片");
    connect(m_picture_files, SIGNAL(clicked()), this, SLOT(on_picture_files_clicked()));
    m_movie_files = new myLabel(this);
    m_movie_files->setText("视频");
    connect(m_movie_files, SIGNAL(clicked()), this, SLOT(on_movie_files_clicked()));
    m_other_files = new myLabel(this);
    m_other_files->setText("更多");
    connect(m_other_files, SIGNAL(clicked()), this, SLOT(on_other_files_clicked()));
    m_empty_area = new myLabel(this);

    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_usb_all);
    m_layout->addWidget(m_note_files);
    m_layout->addWidget(m_ppt_files);
    m_layout->addWidget(m_word_files);
    m_layout->addWidget(m_excel_files);
    m_layout->addWidget(m_pdf_files);
    m_layout->addWidget(m_picture_files);
    m_layout->addWidget(m_movie_files);
    m_layout->addWidget(m_other_files);
    m_layout->addWidget(m_empty_area);

    this->setLayout(m_layout);
}

UsbPanel::~UsbPanel()
{
    delete m_usb_all;
    delete m_note_files;
    delete m_ppt_files;
    delete m_word_files;
    delete m_excel_files;
    delete m_pdf_files;
    delete m_picture_files;
    delete m_movie_files;
    delete m_other_files;
    delete m_empty_area;
    delete m_layout;
}

void UsbPanel::resizeAll()
{
    int average_width = GetSystemMetrics(SM_CXSCREEN) / 10;
    m_usb_all->setFixedSize(average_width, 70);
    m_note_files->setFixedSize(average_width, 70);
    m_ppt_files->setFixedSize(average_width, 70);
    m_word_files->setFixedSize(average_width, 70);
    m_excel_files->setFixedSize(average_width, 70);
    m_pdf_files->setFixedSize(average_width, 70);
    m_picture_files->setFixedSize(average_width, 70);
    m_movie_files->setFixedSize(average_width, 70);
    m_other_files->setFixedSize(average_width, 70);
    m_empty_area->setFixedSize(average_width, 70);
}

QString UsbPanel::generate_note_folder()
{
    QString path_note = m_usbname + ":/Note";
    QDir dir(path_note);
    if(!dir.exists())
        dir.mkpath(path_note);
    return path_note;
}

void UsbPanel::delete_all_popup()
{
    if(filemanagepopup_ppt != NULL)
    {
        filemanagepopup_ppt->hide();
        delete filemanagepopup_ppt;
        filemanagepopup_ppt = NULL;
        m_ppt_files->setStyleSheet("");
    }
    if(filemanagepopup_word != NULL)
    {
        filemanagepopup_word->hide();
        delete filemanagepopup_word;
        filemanagepopup_word = NULL;
        m_word_files->setStyleSheet("");
    }
    if(filemanagepopup_excel != NULL)
    {
        filemanagepopup_excel->hide();
        delete filemanagepopup_excel;
        filemanagepopup_excel = NULL;
        m_excel_files->setStyleSheet("");
    }
    if(filemanagepopup_pdf != NULL)
    {
        filemanagepopup_pdf->hide();
        delete filemanagepopup_pdf;
        filemanagepopup_pdf = NULL;
        m_pdf_files->setStyleSheet("");
    }
    if(filemanagepopup_movie != NULL)
    {
        filemanagepopup_movie->hide();
        delete filemanagepopup_movie;
        filemanagepopup_movie = NULL;
        m_movie_files->setStyleSheet("");
    }
    if(filemanagepopup_other != NULL)
    {
        filemanagepopup_other->hide();
        delete filemanagepopup_other;
        filemanagepopup_other = NULL;
        m_other_files->setStyleSheet("");
    }
}

void UsbPanel::on_usb_all_clicked()
{
    if(filemanagewindow_all == NULL)
    {
        filemanagewindow_all = new FileManageWindow(ALL, m_usbname + ":", this->parentWidget());
        connect(filemanagewindow_all, SIGNAL(myclose()), this, SLOT(on_filemanagewindow_all_close()));
        filemanagewindow_all->setGeometry(GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4, GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
        filemanagewindow_all->show();
        //filemanagewindow->lower();
    }
}

void UsbPanel::on_note_files_clicked()
{
    if(filemanagewindow_note == NULL)
    {
        filemanagewindow_note = new FileManageWindow(NOTE, generate_note_folder(), this->parentWidget());
        connect(filemanagewindow_note, SIGNAL(myclose()), this, SLOT(on_filemanagewindow_note_close()));
        filemanagewindow_note->setGeometry(GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4, GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
        filemanagewindow_note->show();
        //filemanagewindow_note->lower();
        m_note_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
    {
        filemanagewindow_note->hide();
        delete filemanagewindow_note;
        filemanagewindow_note = NULL;
        m_note_files->setStyleSheet("");
    }
}

void UsbPanel::on_ppt_files_clicked()
{
    if(filemanagepopup_ppt == NULL)
    {
        delete_all_popup();
        filemanagepopup_ppt = new FileManagePopup(OFFICEPPT, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_ppt, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_ppt_close()));
        filemanagepopup_ppt->setGeometry(this->pos().x() + m_ppt_files->pos().x(), this->height(), m_ppt_files->width(), m_ppt_files->height() * 6);
        filemanagepopup_ppt->show();
        m_ppt_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_word_files_clicked()
{
    if(filemanagepopup_word == NULL)
    {
        delete_all_popup();
        filemanagepopup_word = new FileManagePopup(OFFICEWORD, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_word, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_word_close()));
        filemanagepopup_word->setGeometry(this->pos().x() + m_word_files->pos().x(), this->height(), m_word_files->width(), m_word_files->height() * 6);
        filemanagepopup_word->show();
        m_word_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_excel_files_clicked()
{
    if(filemanagepopup_excel == NULL)
    {
        delete_all_popup();
        filemanagepopup_excel = new FileManagePopup(OFFICEEXCEL, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_excel, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_excel_close()));
        filemanagepopup_excel->setGeometry(this->pos().x() + m_excel_files->pos().x(), this->height(), m_excel_files->width(), m_excel_files->height() * 6);
        filemanagepopup_excel->show();
        m_excel_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_pdf_files_clicked()
{
    if(filemanagepopup_pdf == NULL)
    {
        delete_all_popup();
        filemanagepopup_pdf = new FileManagePopup(PDF, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_pdf, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_pdf_close()));
        filemanagepopup_pdf->setGeometry(this->pos().x() + m_pdf_files->pos().x(), this->height(), m_pdf_files->width(), m_pdf_files->height() * 6);
        filemanagepopup_pdf->show();
        m_pdf_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_picture_files_clicked()
{
    if(filemanagewindow_pic == NULL)
    {
        filemanagewindow_pic = new FileManageWindow(PICTURES, m_usbname + ":", this->parentWidget());
        connect(filemanagewindow_pic, SIGNAL(myclose()), this, SLOT(on_filemanagewindow_pic_close()));
        filemanagewindow_pic->setGeometry(GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4, GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
        filemanagewindow_pic->show();
        //filemanagewindow_pic->lower();
        m_picture_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
    {
        filemanagewindow_pic->hide();
        delete filemanagewindow_pic;
        filemanagewindow_pic = NULL;
        m_picture_files->setStyleSheet("");
    }
}

void UsbPanel::on_movie_files_clicked()
{
    if(filemanagepopup_movie == NULL)
    {
        delete_all_popup();
        filemanagepopup_movie = new FileManagePopup(MOVIE, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_movie, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_movie_close()));
        filemanagepopup_movie->setGeometry(this->pos().x() + m_movie_files->pos().x(), this->height(), m_movie_files->width(), m_movie_files->height() * 6);
        filemanagepopup_movie->show();
        m_movie_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_other_files_clicked()
{
    if(filemanagepopup_other == NULL)
    {
        delete_all_popup();
        filemanagepopup_other = new FileManagePopup(OTHER, m_usbname + ":", false, false, this->parentWidget());
        connect(filemanagepopup_other, SIGNAL(myclose()), this, SLOT(on_filemanagepopup_other_close()));
        filemanagepopup_other->setGeometry(this->pos().x() + m_other_files->pos().x(), this->height(), m_other_files->width(), m_other_files->height() * 6);
        filemanagepopup_other->show();
        m_other_files->setStyleSheet("background-color: rgb(0, 170, 255);");
    }
    else
        delete_all_popup();
}

void UsbPanel::on_filemanagewindow_all_close()
{
    filemanagewindow_all->hide();
    delete filemanagewindow_all;
    filemanagewindow_all = NULL;
}

void UsbPanel::on_filemanagewindow_note_close()
{
    filemanagewindow_note->hide();
    delete filemanagewindow_note;
    filemanagewindow_note = NULL;
    m_note_files->setStyleSheet("");
}

void UsbPanel::on_filemanagewindow_pic_close()
{
    filemanagewindow_pic->hide();
    delete filemanagewindow_pic;
    filemanagewindow_pic = NULL;
    m_picture_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_ppt_close()
{
    filemanagepopup_ppt->hide();
    delete filemanagepopup_ppt;
    filemanagepopup_ppt = NULL;
    m_ppt_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_word_close()
{
    filemanagepopup_word->hide();
    delete filemanagepopup_word;
    filemanagepopup_word = NULL;
    m_word_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_excel_close()
{
    filemanagepopup_excel->hide();
    delete filemanagepopup_excel;
    filemanagepopup_excel = NULL;
    m_excel_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_pdf_close()
{
    filemanagepopup_pdf->hide();
    delete filemanagepopup_pdf;
    filemanagepopup_pdf = NULL;
    m_pdf_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_movie_close()
{
    filemanagepopup_movie->hide();
    delete filemanagepopup_movie;
    filemanagepopup_movie = NULL;
    m_movie_files->setStyleSheet("");
}

void UsbPanel::on_filemanagepopup_other_close()
{
    filemanagepopup_other->hide();
    delete filemanagepopup_other;
    filemanagepopup_other = NULL;
    m_other_files->setStyleSheet("");
}
