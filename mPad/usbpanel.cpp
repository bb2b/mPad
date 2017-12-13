#include "usbpanel.h"
#include "global.h"

UsbPanel::UsbPanel(QWidget *parent) : QWidget(parent)
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

void UsbPanel::on_usb_all_clicked()
{

}

void UsbPanel::on_note_files_clicked()
{

}

void UsbPanel::on_ppt_files_clicked()
{

}

void UsbPanel::on_word_files_clicked()
{

}

void UsbPanel::on_excel_files_clicked()
{

}

void UsbPanel::on_pdf_files_clicked()
{

}

void UsbPanel::on_picture_files_clicked()
{

}

void UsbPanel::on_movie_files_clicked()
{

}

void UsbPanel::on_other_files_clicked()
{

}
