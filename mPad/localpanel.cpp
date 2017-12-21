#include "localpanel.h"
#include "global.h"

LocalPanel::LocalPanel(QWidget *parent) : QWidget(parent),
    filemanagewindow_all(NULL),
    filemanagewindow_note(NULL),
    filemanagewindow_pic(NULL)
{
    this->setStyleSheet("background-color:rgb(188,188,188);");

    m_all_files = new myLabel(this);
    m_all_files->setText("会议收藏");
    connect(m_all_files, SIGNAL(clicked()), this, SLOT(on_all_files_clicked()));
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
    m_html_collect = new myLabel(this);
    m_html_collect->setText("网络收藏");
    connect(m_html_collect, SIGNAL(clicked()), this, SLOT(on_html_collect_clicked()));
    m_empty_area = new myLabel(this);

    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_all_files);
    m_layout->addWidget(m_note_files);
    m_layout->addWidget(m_ppt_files);
    m_layout->addWidget(m_word_files);
    m_layout->addWidget(m_excel_files);
    m_layout->addWidget(m_pdf_files);
    m_layout->addWidget(m_picture_files);
    m_layout->addWidget(m_movie_files);
    m_layout->addWidget(m_other_files);
    m_layout->addWidget(m_html_collect);
    m_layout->addWidget(m_empty_area);

    this->setLayout(m_layout);
}

LocalPanel::~LocalPanel()
{
    delete m_all_files;
    delete m_note_files;
    delete m_ppt_files;
    delete m_word_files;
    delete m_excel_files;
    delete m_pdf_files;
    delete m_picture_files;
    delete m_movie_files;
    delete m_other_files;
    delete m_html_collect;
    delete m_empty_area;
    delete m_layout;
}

void LocalPanel::resizeAll()
{
    int average_width = GetSystemMetrics(SM_CXSCREEN) / 11;
    m_all_files->setFixedSize(average_width, 70);
    m_note_files->setFixedSize(average_width, 70);
    m_ppt_files->setFixedSize(average_width, 70);
    m_word_files->setFixedSize(average_width, 70);
    m_excel_files->setFixedSize(average_width, 70);
    m_pdf_files->setFixedSize(average_width, 70);
    m_picture_files->setFixedSize(average_width, 70);
    m_movie_files->setFixedSize(average_width, 70);
    m_other_files->setFixedSize(average_width, 70);
    m_html_collect->setFixedSize(average_width, 70);
    m_empty_area->setFixedSize(average_width, 70);
}

void LocalPanel::on_all_files_clicked()
{
    if(filemanagewindow_all == NULL)
    {
        filemanagewindow_all = new FileManageWindow(ALL, generate_folder_on_desktop(), this->parentWidget());
        connect(filemanagewindow_all, SIGNAL(myclose()), this, SLOT(on_filemanagewindow_all_close()));
        filemanagewindow_all->setGeometry(GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4, GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
        filemanagewindow_all->show();
        //filemanagewindow->lower();
    }
}

void LocalPanel::on_note_files_clicked()
{
    if(filemanagewindow_note == NULL)
    {
        filemanagewindow_note = new FileManageWindow(NOTE, generate_folder_on_desktop() + "/Note", this->parentWidget());
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

void LocalPanel::on_ppt_files_clicked()
{

}

void LocalPanel::on_word_files_clicked()
{

}

void LocalPanel::on_excel_files_clicked()
{

}

void LocalPanel::on_pdf_files_clicked()
{

}

void LocalPanel::on_picture_files_clicked()
{
    if(filemanagewindow_pic == NULL)
    {
        filemanagewindow_pic = new FileManageWindow(PICTURES, generate_folder_on_desktop(), this->parentWidget());
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

void LocalPanel::on_movie_files_clicked()
{

}

void LocalPanel::on_other_files_clicked()
{

}

void LocalPanel::on_html_collect_clicked()
{

}

void LocalPanel::on_filemanagewindow_all_close()
{
    filemanagewindow_all->hide();
    delete filemanagewindow_all;
    filemanagewindow_all = NULL;
}

void LocalPanel::on_filemanagewindow_note_close()
{
    filemanagewindow_note->hide();
    delete filemanagewindow_note;
    filemanagewindow_note = NULL;
    m_note_files->setStyleSheet("");
}

void LocalPanel::on_filemanagewindow_pic_close()
{
    filemanagewindow_pic->hide();
    delete filemanagewindow_pic;
    filemanagewindow_pic = NULL;
    m_picture_files->setStyleSheet("");
}
