#include <QGroupBox>
#include "file_manage_popup.h"
#include "global.h"

FileManagePopup::FileManagePopup(int filtertype, QString directory, bool onBottom, bool newHtml, QWidget *parent) : QWidget(parent),
    current_directory(directory),
    m_onBottom(onBottom),
    m_newHtml(newHtml),
    g_filtertype(filtertype)
{
    m_title_area = new QWidget(this);
    m_title_area->setStyleSheet("QWidget{background-color:rgb(254,254,254);}");
    m_hlayout = new QHBoxLayout();
    m_hlayout->setContentsMargins(0,0,0,0);
    m_hlayout->setSpacing(0);
    if(m_newHtml)
    {
        m_newHtml_button = new QPushButton();
        m_newHtml_button->setText("添加网址");
        connect(m_newHtml_button, SIGNAL(clicked()), this, SLOT(on_newHtml_button_clicked()));
        m_hlayout->addWidget(m_newHtml_button);
    }
    m_setting_button = new QPushButton();
    m_setting_button->setText("设置");
    connect(m_setting_button, SIGNAL(clicked()), this, SLOT(on_setting_button_clicked()));
    m_hlayout->addWidget(m_setting_button);
    m_close_button = new QPushButton();
    m_close_button->setText("关闭");
    connect(m_close_button, SIGNAL(clicked()), this, SLOT(on_close_button_clicked()));
    m_hlayout->addWidget(m_close_button);
    m_title_area->setLayout(m_hlayout);

    QDir current_dir(current_directory);

    m_scrollarea = new QScrollArea(this);
    m_scrollarea->setStyleSheet("background-color:rgb(254,254,254);");
    m_scrollarea->setFrameStyle(QFrame::NoFrame);
    m_scrollarea->setAlignment(Qt::AlignCenter);

    m_vlayout = new QVBoxLayout();
    m_vlayout->setContentsMargins(0,0,0,0);
    m_vlayout->setSpacing(0);
    if(current_dir.exists())
    {
        QStringList filter;
        QList<QFileInfoList> list_fileinfo_list;
        switch (g_filtertype) {
        case OFFICEPPT:
            filter << "*.pptx" << "*.ppt";
            list_fileinfo_list = sort_by_createdtime(get_file_list(current_directory, filter));
            break;
        case OFFICEWORD:
            filter << "*.docx" << "*.doc";
            list_fileinfo_list = sort_by_createdtime(get_file_list(current_directory, filter));
            break;
        case OFFICEEXCEL:
            filter << "*.xlsx" << "*.xls";
            list_fileinfo_list = sort_by_createdtime(get_file_list(current_directory, filter));
            break;
        case PDF:
            filter << "*.pdf";
            list_fileinfo_list = sort_by_createdtime(get_file_list(current_directory, filter));
            break;
        case MOVIE:
            filter << "*.mp4" << "*.avi" << "*.mov" << "*.wmv";
            list_fileinfo_list = sort_by_createdtime(get_file_list(current_directory, filter));
            break;
        case OTHER:
        {
            QStringList filter_need;
            filter_need << "*.pptx" << "*.ppt" << "*.docx" << "*.doc" << "*.xlsx" << "*.xls" << "*.pdf" << "*.mp4" << "*.avi" << "*.mov" << "*.wmv" << "*.bmp" << "*.dib" << "*.gif" << "*.jfif" << "*.jpe" << "*.jpeg" << "*.jpg" << "*.png" << "*.tif" << "*.tiff" << "*.wdp";
            QFileInfoList infolist_need = get_file_list(current_directory, filter_need);
            QFileInfoList infolist_all = get_file_list_no_filter(current_directory);
            if(infolist_all.size() > 0)
            {
                for(int i = 0; i < infolist_need.size(); i++)
                    infolist_all.removeOne(infolist_need.at(i));
            }
            list_fileinfo_list = sort_by_createdtime(infolist_all);
        }
            break;
        default:
            break;
        }
        if(list_fileinfo_list.size() > 0)
        {
            for(int i = 0; i < list_fileinfo_list.size(); i++)
            {
                if(list_fileinfo_list.at(i).size() > 0)
                {
                    QGroupBox *groupbox = new QGroupBox();
                    if(list_fileinfo_list.at(i).at(0).created().date() == QDateTime::currentDateTime().date())
                        groupbox->setTitle("今天");
                    else
                        groupbox->setTitle(list_fileinfo_list.at(i).at(0).created().toString("yyyy/MM/dd"));
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
                    QVBoxLayout *vlayout = new QVBoxLayout();
                    vlayout->setContentsMargins(0,0,0,0);
                    vlayout->setSpacing(0);
                    for(int j = 0; j < list_fileinfo_list.at(i).size(); j++)
                    {
                        File *file = new File(false, list_fileinfo_list.at(i).at(j));
                        vlayout->addWidget(file);
                    }
                    groupbox->setLayout(vlayout);
                    m_vlayout->addWidget(groupbox);
                }
            }
        }
    }
    m_files_area = new QWidget();
    m_files_area->setLayout(m_vlayout);
    m_scrollarea->setWidget(m_files_area);
}

FileManagePopup::~FileManagePopup()
{
    if(m_newHtml) delete m_newHtml_button;
    delete m_setting_button;
    delete m_close_button;
    delete m_hlayout;
    delete m_title_area;
}

QFileInfoList FileManagePopup::get_file_list(QString path, QStringList filters)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(filters);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = get_file_list(name, filters);
         file_list.append(child_file_list);
    }

    return file_list;
}

QFileInfoList FileManagePopup::get_file_list_no_filter(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = get_file_list_no_filter(name);
         file_list.append(child_file_list);
    }

    return file_list;
}

QList<QFileInfoList> FileManagePopup::sort_by_createdtime(QFileInfoList filelist)
{
    std::sort(filelist.begin(), filelist.end(), FileManagePopup::compareCreateTime);
    QFileInfoList infolist_temp;
    QList<QFileInfoList> list_temp;
    for(int i = 0; i < filelist.size(); i++)
    {
        if(i != 0 && filelist.at(i).created().date() < filelist.at(i - 1).created().date())
        {
            list_temp << infolist_temp;
            infolist_temp.clear();
        }
        infolist_temp << filelist.at(i);
    }
    list_temp << infolist_temp;
    return list_temp;
}

bool FileManagePopup::compareCreateTime(const QFileInfo &fileinfo1, const QFileInfo &fileinfo2)
{
    return fileinfo1.created() > fileinfo2.created();
}

void FileManagePopup::on_setting_button_clicked()
{

}

void FileManagePopup::on_close_button_clicked()
{
    emit myclose();
}

void FileManagePopup::on_newHtml_button_clicked()
{

}

void FileManagePopup::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
    if(m_onBottom)
    {
        m_title_area->setGeometry(0, 0, w, h / 10);
        m_scrollarea->setGeometry(0, m_title_area->height(), w, h - m_title_area->height());
    }
    else
    {
        m_scrollarea->setGeometry(0, 0, w, h * 9 / 10);
        m_title_area->setGeometry(0, m_scrollarea->height(), w, h - m_scrollarea->height());
    }
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
            file->setFixedSize(w - 10, (w - 10) / 3);
        }
        groupbox->setFixedSize(w, (filelist.size() - 1) * (w - 10) / 3 + 15);
        h_count += groupbox->height();
    }
    m_files_area->setGeometry(0, 0, w - 10, h_count);
}
