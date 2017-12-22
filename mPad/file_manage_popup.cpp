#include "file_manage_popup.h"
#include "global.h"

FileManagePopup::FileManagePopup(int filtertype, QString directory, bool onBottom, bool newHtml, QWidget *parent) : QWidget(parent),
    current_directory(directory),
    m_onBottom(onBottom),
    m_newHtml(newHtml),
    g_filtertype(filtertype)
{
    m_title_area = new QWidget(this);
    m_title_area->setStyleSheet("QWidget{background-color:white;}");
    m_hlayout = new QHBoxLayout();
    m_hlayout->setContentsMargins(0,0,0,0);
    m_hlayout->setSpacing(0);
    if(m_newHtml)
    {
        m_newHtml_button = new QPushButton();
        m_newHtml_button->setText("Ìí¼ÓÍøÖ·");
        connect(m_newHtml_button, SIGNAL(clicked()), this, SLOT(on_newHtml_button_clicked()));
        m_hlayout->addWidget(m_newHtml_button);
    }
    m_setting_button = new QPushButton();
    m_setting_button->setText("ÉèÖÃ");
    connect(m_setting_button, SIGNAL(clicked()), this, SLOT(on_setting_button_clicked()));
    m_hlayout->addWidget(m_setting_button);
    m_close_button = new QPushButton();
    m_close_button->setText("¹Ø±Õ");
    connect(m_close_button, SIGNAL(clicked()), this, SLOT(on_close_button_clicked()));
    m_hlayout->addWidget(m_close_button);
    m_title_area->setLayout(m_hlayout);

    QDir current_dir(current_directory);

    m_scrollarea = new QScrollArea(this);
    m_scrollarea->setStyleSheet("QScrollArea{border-width:2px;border-color:black;border-style:solid;}");
    m_scrollarea->setFrameStyle(QFrame::NoFrame);
    m_scrollarea->setAlignment(Qt::AlignCenter);

    m_vlayout = new QVBoxLayout();
    m_vlayout->setContentsMargins(0,0,0,0);
    m_vlayout->setSpacing(0);
    if(current_dir.exists())
    {
        switch (g_filtertype) {
        case OFFICEPPT:
        {

        }
            break;
        case OFFICEWORD:
        {

        }
            break;
        case OFFICEEXCEL:
        {

        }
            break;
        case PDF:
        {

        }
            break;
        case MOVIE:
        {

        }
            break;
        case OTHER:
        {

        }
            break;
        default:
            break;
        }
    }
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

QList<QFileInfoList> FileManagePopup::sort_by_createdtime(QFileInfoList filelist)
{
    qSort(filelist.begin(), filelist.end(), compareCreateTime);
    QFileInfoList infolist_temp;
    QList<QFileInfoList> list_temp;
    for(int i = 0; i < filelist.size(); i++)
    {
        if(i != 0 && filelist.at(i).created().date() > filelist.at(i - 1).created().date())
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
    return fileinfo1.created() < fileinfo2.created();
}
