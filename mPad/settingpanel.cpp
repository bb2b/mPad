#include "settingpanel.h"
#include "global.h"

SettingPanel::SettingPanel(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setStyleSheet("background-color:gray;");

    m_setting = new QPushButton(this);
    m_setting->setText("设置");
    connect(m_setting, SIGNAL(clicked()), this, SLOT(on_setting_btn_clicked()));
    m_eject = new QPushButton(this);
    m_eject->setText("弹出");
    connect(m_eject, SIGNAL(clicked()), this, SLOT(on_eject_btn_clicked()));
    m_about = new QPushButton(this);
    m_about->setText("关于");
    connect(m_about, SIGNAL(clicked()), this, SLOT(on_about_btn_clicked()));
    m_exit = new QPushButton(this);
    m_exit->setText("退出");
    connect(m_exit, SIGNAL(clicked()), this, SLOT(on_exit_btn_clicked()));

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_setting);
    m_layout->addWidget(m_eject);
    m_layout->addWidget(m_about);
    m_layout->addWidget(m_exit);

    this->setLayout(m_layout);
}

SettingPanel::~SettingPanel()
{
    delete m_setting;
    delete m_eject;
    delete m_about;
    delete m_exit;
    delete m_layout;
}

void SettingPanel::resizeAll()
{
    m_setting->setFixedSize(80, 80);
    m_eject->setFixedSize(80, 80);
    m_about->setFixedSize(80, 80);
    m_exit->setFixedSize(80, 80);
}

void SettingPanel::on_setting_btn_clicked()
{

}

void SettingPanel::on_eject_btn_clicked()
{

}

void SettingPanel::on_about_btn_clicked()
{

}

void SettingPanel::on_exit_btn_clicked()
{
    exit(0);
}
