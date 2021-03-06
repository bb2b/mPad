﻿#include "file_manage_window.h"
#include <QGroupBox>
#include <QStringList>
#include <QGridLayout>
#include <QObjectList>
#include <QScrollBar>
#include "global.h"

FileManageWindow::FileManageWindow(int filtertype, QString directory, QWidget *parent) : QDialog(parent),
    m_vlayout(NULL),
    m_files_area(NULL),
    original_directory(directory),
    current_directory(directory),
    g_filtertype(filtertype)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    //this->setStyleSheet("QDialog{border-width:2px;border-color:black;border-style:solid;}");

    m_title_area = new QWidget(this);
    m_title_area->setStyleSheet("QWidget{background-color:rgb(53,162,213);}");
    m_hlayout = new QHBoxLayout();
    m_hlayout->setContentsMargins(10,0,0,0);
    m_hlayout->setSpacing(0);
    m_directory_label = new QLabel();
    m_directory_label->setText(original_directory);
    m_return_button = new QPushButton();
    m_return_button->setText("返回");
    connect(m_return_button, SIGNAL(clicked()), this, SLOT(on_return_button_clicked()));
    m_manage_button = new QPushButton();
    m_manage_button->setText("文件搜索");
    connect(m_manage_button, SIGNAL(clicked()), this, SLOT(on_manage_button_clicked()));
    m_close_button = new QPushButton();
    m_close_button->setText("关闭");
    connect(m_close_button, SIGNAL(clicked()), this, SLOT(on_close_button_clicked()));
    m_hlayout->addWidget(m_directory_label);
    m_hlayout->addWidget(m_return_button);
    m_hlayout->addWidget(m_manage_button);
    m_hlayout->addWidget(m_close_button);
    m_title_area->setLayout(m_hlayout);

    m_manage_area = new QWidget(this);
    m_manage_area->setStyleSheet("QWidget{background-color:rgb(202,202,202);}");
    m_generate_pdf_button = new QPushButton(m_manage_area);
    m_generate_pdf_button->setText("生成pdf");
    m_send_button = new QPushButton(m_manage_area);
    m_send_button->setText("作为附件发送");
    m_save_button = new QPushButton(m_manage_area);
    m_save_button->setText("存到U盘");
    m_delete_button = new QPushButton(m_manage_area);
    m_delete_button->setText("删除");
    m_print_button = new QPushButton(m_manage_area);
    m_print_button->setText("打印");
    m_share_button = new QPushButton(m_manage_area);
    m_share_button->setText("扫码分享");
    m_manage_area->setVisible(false);

    m_share_label = new QLabel(this);
    m_share_label->setVisible(false);

    current_dir = new QDir(directory);

    m_scrollarea = new QScrollArea(this);
    m_scrollarea->setStyleSheet("background-color:rgb(254,254,254);");
    m_scrollarea->setFrameStyle(QFrame::NoFrame);
    m_scrollarea->setAlignment(Qt::AlignCenter);

    QScrollBar *scrollbar_h = m_scrollarea->horizontalScrollBar();
    scrollbar_h->setStyleSheet("QScrollBar:horizontal{height: 8px; padding-left: 8px; padding-right: 8px; background: rgb(231,231,231)}"
                               "QScrollBar::handle:horizontal{height: 8px; border-radius: 3px; background: rgb(53,162,213)}"
                               "QScrollBar::handle:horizontal:hover{height: 8px; border-radius: 3px; background: rgb(53,162,213)}"
                               "QScrollBar::sub-line:horizontal{height: 8px; width: 8px; subcontrol-position: left; border-image: url(:/pic/left.png)}"
                               "QScrollBar::add-line:horizontal{height: 8px; width: 8px; subcontrol-position: right; border-image: url(:/pic/right.png)}"
                               "QScrollBar::add-page:horizontal{background: rgb(231,231,231)}"
                               "QScrollBar::sub-page:horizontal{background: rgb(231,231,231)}");
    QScrollBar *scrollbar_v = m_scrollarea->verticalScrollBar();
    scrollbar_v->setStyleSheet("QScrollBar:vertical{width: 8px; padding-top: 8px; padding-bottom: 8px; background: rgb(231,231,231)}"
                               "QScrollBar::handle:vertical{width: 8px; border-radius: 3px; background: rgb(53,162,213)}"
                               "QScrollBar::handle:vertical:hover{width: 8px; border-radius: 3px; background: rgb(53,162,213)}"
                               "QScrollBar::add-line:vertical{height: 8px; width: 8px; subcontrol-position: bottom; border-image: url(:/pic/top.png)}"
                               "QScrollBar::sub-line:vertical{height: 8px; width: 8px; subcontrol-position: top; border-image: url(:/pic/bottom.png)}"
                               "QScrollBar::add-page:vertical{background: rgb(231,231,231)}"
                               "QScrollBar::sub-page:vertical{background: rgb(231,231,231)}");

    init_files_area();
}

FileManageWindow::~FileManageWindow()
{
    delete m_directory_label;
    delete m_return_button;
    delete m_manage_button;
    delete m_close_button;
    delete m_hlayout;
    delete m_title_area;
    delete m_generate_pdf_button;
    delete m_send_button;
    delete m_save_button;
    delete m_delete_button;
    delete m_print_button;
    delete m_share_button;
    delete m_manage_area;
    delete m_share_label;
    delete m_vlayout;
    delete m_files_area;
    delete m_scrollarea;
    delete current_dir;
}

void FileManageWindow::init_files_area()
{
    if(m_vlayout != NULL)
    {
        delete m_vlayout;
        m_vlayout = NULL;
    }
    m_vlayout = new QVBoxLayout();
    m_vlayout->setContentsMargins(0,0,0,0);
    m_vlayout->setSpacing(0);
    if(current_dir->exists())
    {
        //列出“文件夹”,除了批注文件 窗口，其他窗口都要列出文件夹
        QFileInfoList dirs_list = current_dir->entryInfoList(QDir::NoDotAndDotDot | QDir::Hidden | QDir::Dirs);
        if(dirs_list.size() > 0 && g_filtertype != NOTE)
        {
            QGroupBox *groupbox = new QGroupBox();
            groupbox->setTitle("文件夹");
            groupbox->setStyleSheet(""
                             "QGroupBox {"\
                                   "border-width:2px;"\
                                   "border-style:solid;"\
                                   "border-color:lightGray;"\
                                   "margin-top: 12px;"\
                                   "border-left:none;"\
                                   "border-right:none;"\
                                   "border-bottom:none;"\
                              "}"\
                              "QGroupBox::title {"\
                                   "subcontrol-origin: margin;"\
                                   "subcontrol-position: top left;"\
                                   "left:0px;"\
                                   "background-color:lightGray;"\
                              "}");
            QGridLayout *gridlayout = new QGridLayout();
            gridlayout->setContentsMargins(0,0,0,0);
            gridlayout->setSpacing(0);
            int h = 0;
            int v = 0;
            for(int i = 0; i < dirs_list.size(); i++)
            {
                File *file = new File(true, dirs_list.at(i));
                connect(file, SIGNAL(clicked()), this, SLOT(on_folder_clicked()));
                gridlayout->addWidget(file, h, v);
                if(v >= 7)
                {
                    h++;
                    v=0;
                }
                else
                    v++;
            }
            if(dirs_list.size() < 8)
            {
                QHBoxLayout *temp_hlayout = new QHBoxLayout();
                temp_hlayout->addStretch();
                gridlayout->addLayout(temp_hlayout, 0, dirs_list.size());
            }
            groupbox->setLayout(gridlayout);
            m_vlayout->addWidget(groupbox);
        }
        //列出“文档”,只有会议收藏窗口需要列出文档
        QFileInfoList files_list = current_dir->entryInfoList(QStringList() << "*.pdf" << "*.docx" << "*.doc" << "*.xlsx" << "*.xls" << "*.pptx" << "*.ppt");
        if(files_list.size() > 0 && g_filtertype == ALL)
        {
            QGroupBox *groupbox = new QGroupBox();
            groupbox->setTitle("文档");
            groupbox->setStyleSheet(""
                             "QGroupBox {"\
                                   "border-width:2px;"\
                                   "border-style:solid;"\
                                   "border-color:lightGray;"\
                                   "margin-top: 12px;"\
                                   "border-left:none;"\
                                   "border-right:none;"\
                                   "border-bottom:none;"\
                              "}"\
                              "QGroupBox::title {"\
                                   "subcontrol-origin: margin;"\
                                   "subcontrol-position: top left;"\
                                   "left:0px;"\
                                   "background-color:lightGray;"\
                              "}");
            QGridLayout *gridlayout = new QGridLayout();
            gridlayout->setContentsMargins(0,0,0,0);
            gridlayout->setSpacing(0);
            int h = 0;
            int v = 0;
            for(int i = 0; i < files_list.size(); i++)
            {
                File *file = new File(true, files_list.at(i));
                gridlayout->addWidget(file, h, v);
                if(v >= 7)
                {
                    h++;
                    v=0;
                }
                else
                    v++;
            }
            if(files_list.size() < 8)
            {
                QHBoxLayout *temp_hlayout = new QHBoxLayout();
                temp_hlayout->addStretch();
                gridlayout->addLayout(temp_hlayout, 0, files_list.size());
            }
            groupbox->setLayout(gridlayout);
            m_vlayout->addWidget(groupbox);
        }
        //列出“图片”
        QFileInfoList pics_list = current_dir->entryInfoList(QStringList() << "*.bmp" << "*.gif" << "*.jpe" << "*.jpeg" << "*.jpg" << "*.png");
        if(pics_list.size() > 0)
        {
            QGroupBox *groupbox = new QGroupBox();
            groupbox->setTitle("图片");
            groupbox->setStyleSheet(""
                             "QGroupBox {"\
                                   "border-width:2px;"\
                                   "border-style:solid;"\
                                   "border-color:lightGray;"\
                                   "margin-top: 12px;"\
                                   "border-left:none;"\
                                   "border-right:none;"\
                                   "border-bottom:none;"\
                              "}"\
                              "QGroupBox::title {"\
                                   "subcontrol-origin: margin;"\
                                   "subcontrol-position: top left;"\
                                   "left:0px;"\
                                   "background-color:lightGray;"\
                              "}");
            QGridLayout *gridlayout = new QGridLayout();
            gridlayout->setContentsMargins(0,0,0,0);
            gridlayout->setSpacing(0);
            int h = 0;
            int v = 0;
            for(int i = 0; i < pics_list.size(); i++)
            {
                File *file = new File(true, pics_list.at(i));
                gridlayout->addWidget(file, h, v);
                if(v >= 7)
                {
                    h++;
                    v=0;
                }
                else
                    v++;
            }
            if(pics_list.size() < 8)
            {
                QHBoxLayout *temp_hlayout = new QHBoxLayout();
                temp_hlayout->addStretch();
                gridlayout->addLayout(temp_hlayout, 0, pics_list.size());
            }
            groupbox->setLayout(gridlayout);
            m_vlayout->addWidget(groupbox);
        }
        //列出“视频”,只有会议收藏窗口需要列出视频
        QFileInfoList movies_list = current_dir->entryInfoList(QStringList() << "*.mp4" << "*.avi" << "*.mov" << "*.wmv");
        if(movies_list.size() > 0 && g_filtertype == ALL)
        {
            QGroupBox *groupbox = new QGroupBox();
            groupbox->setTitle("视频");
            groupbox->setStyleSheet(""
                             "QGroupBox {"\
                                   "border-width:2px;"\
                                   "border-style:solid;"\
                                   "border-color:lightGray;"\
                                   "margin-top: 12px;"\
                                   "border-left:none;"\
                                   "border-right:none;"\
                                   "border-bottom:none;"\
                              "}"\
                              "QGroupBox::title {"\
                                   "subcontrol-origin: margin;"\
                                   "subcontrol-position: top left;"\
                                   "left:0px;"\
                                   "background-color:lightGray;"\
                              "}");
            QGridLayout *gridlayout = new QGridLayout();
            gridlayout->setContentsMargins(0,0,0,0);
            gridlayout->setSpacing(0);
            int h = 0;
            int v = 0;
            for(int i = 0; i < movies_list.size(); i++)
            {
                File *file = new File(true, movies_list.at(i));
                gridlayout->addWidget(file, h, v);
                if(v >= 7)
                {
                    h++;
                    v=0;
                }
                else
                    v++;
            }
            if(movies_list.size() < 8)
            {
                QHBoxLayout *temp_hlayout = new QHBoxLayout();
                temp_hlayout->addStretch();
                gridlayout->addLayout(temp_hlayout, 0, movies_list.size());
            }
            groupbox->setLayout(gridlayout);
            m_vlayout->addWidget(groupbox);
        }
        //列出“其他”
        if(g_filtertype == ALL)
        {
            QFileInfoList all_list = current_dir->entryInfoList(QDir::NoDotAndDotDot | QDir::Hidden | QDir::Dirs | QDir::Files);
            if(all_list.size() > 0)
            {
                if(dirs_list.size() > 0)
                {
                    for(int i = 0; i < dirs_list.size(); i++)
                    {
                        all_list.removeOne(dirs_list.at(i));
                    }
                }
                if(files_list.size() > 0)
                {
                    for(int i = 0; i < files_list.size(); i++)
                    {
                        all_list.removeOne(files_list.at(i));
                    }
                }
                if(pics_list.size() > 0)
                {
                    for(int i = 0; i < pics_list.size(); i++)
                    {
                        all_list.removeOne(pics_list.at(i));
                    }
                }
                if(movies_list.size() > 0)
                {
                    for(int i = 0; i < movies_list.size(); i++)
                    {
                        all_list.removeOne(movies_list.at(i));
                    }
                }
                if(all_list.size() > 0)
                {
                    QGroupBox *groupbox = new QGroupBox();
                    groupbox->setTitle("其它");
                    groupbox->setStyleSheet(""
                                     "QGroupBox {"\
                                           "border-width:2px;"\
                                           "border-style:solid;"\
                                           "border-color:lightGray;"\
                                           "margin-top: 12px;"\
                                           "border-left:none;"\
                                           "border-right:none;"\
                                           "border-bottom:none;"\
                                      "}"\
                                      "QGroupBox::title {"\
                                           "subcontrol-origin: margin;"\
                                           "subcontrol-position: top left;"\
                                           "left:0px;"\
                                           "background-color:lightGray;"\
                                      "}");
                    QGridLayout *gridlayout = new QGridLayout();
                    gridlayout->setContentsMargins(0,0,0,0);
                    gridlayout->setSpacing(0);
                    int h = 0;
                    int v = 0;
                    for(int i = 0; i < all_list.size(); i++)
                    {
                        File *file = new File(true, all_list.at(i));
                        gridlayout->addWidget(file, h, v);
                        if(v >= 7)
                        {
                            h++;
                            v=0;
                        }
                        else
                            v++;
                    }
                    if(all_list.size() < 8)
                    {
                        QHBoxLayout *temp_hlayout = new QHBoxLayout();
                        temp_hlayout->addStretch();
                        gridlayout->addLayout(temp_hlayout, 0, all_list.size());
                    }
                    groupbox->setLayout(gridlayout);
                    m_vlayout->addWidget(groupbox);
                }
            }
        }
    }
    m_vspacer = new QVBoxLayout();
    m_vspacer->addStretch();
    m_vlayout->addLayout(m_vspacer);
    if(m_files_area != NULL)
    {
        delete m_files_area;
        m_files_area = NULL;
    }
    m_files_area = new QWidget();
    m_files_area->setLayout(m_vlayout);
    m_scrollarea->setWidget(m_files_area);
}

void FileManageWindow::on_return_button_clicked()
{
    if(current_directory == original_directory)
        return;

    if(current_dir->cdUp())
    {
        current_directory = current_dir->path();
        m_directory_label->setText(current_directory);
        init_files_area();
        QResizeEvent event(QSize(this->width(), this->height()), QSize(this->width(), this->height()));
        resizeEvent(&event);
    }
}

void FileManageWindow::on_manage_button_clicked()
{

}

void FileManageWindow::on_close_button_clicked()
{
    emit myclose();
}

void FileManageWindow::on_folder_clicked()
{
    File *file = qobject_cast<File *>(sender());
    if(current_dir->cd(file->m_fileinfo.fileName()))
    {
        current_directory = current_directory + "/" + file->m_fileinfo.fileName();
        m_directory_label->setText(current_directory);
        init_files_area();
        QResizeEvent event(QSize(this->width(), this->height()), QSize(this->width(), this->height()));
        resizeEvent(&event);
    }
}

void FileManageWindow::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
}

void FileManageWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint new_point = this->pos() + event->pos() - m_last_point;
    if(b_move && new_point.x() >= 0 && new_point.x() + this->width() <= GetSystemMetrics(SM_CXSCREEN) && new_point.y() >= 0 && new_point.y() + this->height() <= GetSystemMetrics(SM_CYSCREEN))
    {
        this->move(new_point);
    }
    else
        m_last_point = event->pos();
}

void FileManageWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    b_move = false;
}

void FileManageWindow::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
    m_title_area->setGeometry(0, 0, w, h / 12);
    m_return_button->setFixedSize(w / 12, h / 12);
    m_manage_button->setFixedSize(w / 12, h / 12);
    m_close_button->setFixedSize(w / 24, h / 12);
    m_scrollarea->setGeometry(0, m_title_area->height(), w, h - m_title_area->height());
    QObjectList list = m_files_area->children();
    //去掉第一个，因为第一个是layout
    int h_count = 0;
    for(int i = 1; i < list.size(); i++)
    {
        QGroupBox *groupbox = (QGroupBox *)list[i];
        QObjectList filelist = groupbox->children();
        for(int j = 1; j < filelist.size(); j++)
        {
            File *file = (File *)filelist[j];
            file->setFixedSize((w - 10) / 8, (w - 10) / 8);
        }
        groupbox->setFixedSize(w - 10, ((filelist.size() - 1) / 8 + ((filelist.size() - 1) % 8 > 0 ? 1 : 0)) * (w - 10) / 8 + 15);
        h_count += groupbox->height();
    }
    if(h_count < m_scrollarea->height())
        m_files_area->setGeometry(0, 0, w - 10, m_scrollarea->height());
    else
        m_files_area->setGeometry(0, 0, w - 10, h_count);
}
