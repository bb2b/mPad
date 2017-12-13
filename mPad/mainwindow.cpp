#include "mainwindow.h"
#include "global.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    b_settingpanel_visible(true),
    b_localpanel_visible(true),
    b_usbpanel_visible(true)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setStyleSheet("background-color: rgb(255, 170, 127);");

    m_settingpanel_ctrl_btn = new QPushButton(this);
    m_settingpanel_ctrl_btn->setText("隐藏");
    connect(m_settingpanel_ctrl_btn, SIGNAL(clicked()), this, SLOT(on_settingpanel_ctrl_btn_clicked()));
    m_settingpanel = new SettingPanel(this);

    m_localpanel_ctrl_btn = new QPushButton(this);
    m_localpanel_ctrl_btn->setText("隐藏");
    connect(m_localpanel_ctrl_btn, SIGNAL(clicked()), this, SLOT(on_localpanel_ctrl_btn_clicked()));
    m_localpanel = new LocalPanel(this);
    m_localpanel_ctrl_btn->raise();

    m_usbpanel_ctrl_btn = new QPushButton(this);
    m_usbpanel_ctrl_btn->setText("隐藏");
    connect(m_usbpanel_ctrl_btn, SIGNAL(clicked()), this, SLOT(on_usbpanel_ctrl_btn_clicked()));
    m_usbpanel = new UsbPanel(this);
    m_usbpanel_ctrl_btn->raise();

    connect(&settingpanel_timer, SIGNAL(timeout()), this, SLOT(on_settingpanel_timeout()));
    connect(&localpanel_timer, SIGNAL(timeout()), this, SLOT(on_localpanel_timeout()));
    connect(&usbpanel_timer, SIGNAL(timeout()), this, SLOT(on_usbpanel_timeout()));
}

MainWindow::~MainWindow()
{
    delete m_settingpanel_ctrl_btn;
    delete m_settingpanel;
    delete m_localpanel_ctrl_btn;
    delete m_localpanel;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    static int width = 0;
    if (width != GetSystemMetrics(SM_CXSCREEN)) {
        width = GetSystemMetrics(SM_CXSCREEN);
        m_settingpanel->resizeAll();
        m_settingpanel->setGeometry(0, GetSystemMetrics(SM_CYSCREEN)/2, 80, 320);
        m_settingpanel_ctrl_btn->setGeometry(80, m_settingpanel->pos().y() + m_settingpanel->height() / 2 - 20, 40, 40);
        m_localpanel->resizeAll();
        m_localpanel->setGeometry(0, GetSystemMetrics(SM_CYSCREEN) - 70, GetSystemMetrics(SM_CXSCREEN), 70);
        m_localpanel_ctrl_btn->setGeometry(GetSystemMetrics(SM_CXSCREEN) * 21 / 22 - 20, GetSystemMetrics(SM_CYSCREEN) - 55, 40, 40);
        m_usbpanel->resizeAll();
        m_usbpanel->setGeometry(0, 0, GetSystemMetrics(SM_CXSCREEN), 70);
        m_usbpanel_ctrl_btn->setGeometry(GetSystemMetrics(SM_CXSCREEN) * 19 / 20 - 20, 15, 40, 40);
    }
}

void MainWindow::on_settingpanel_ctrl_btn_clicked()
{
    if(settingpanel_timer.isActive())
        settingpanel_timer.stop();
    settingpanel_timer.start(2);
}

void MainWindow::on_localpanel_ctrl_btn_clicked()
{
    if(localpanel_timer.isActive())
        localpanel_timer.stop();
    localpanel_timer.start(2);
}

void MainWindow::on_usbpanel_ctrl_btn_clicked()
{
    if(usbpanel_timer.isActive())
        usbpanel_timer.stop();
    usbpanel_timer.start(2);
}

void MainWindow::on_settingpanel_timeout()
{
    if(b_settingpanel_visible)
    {
        m_settingpanel->move(m_settingpanel->pos().x() - 1, m_settingpanel->pos().y());
        m_settingpanel_ctrl_btn->move(m_settingpanel_ctrl_btn->pos().x() - 1, m_settingpanel_ctrl_btn->pos().y());
        if(m_settingpanel->x() + m_settingpanel->width() == 0)
        {
            m_settingpanel_ctrl_btn->setText("显示");
            b_settingpanel_visible = false;
            settingpanel_timer.stop();
        }
    }
    else
    {
        m_settingpanel->move(m_settingpanel->pos().x() + 1, m_settingpanel->pos().y());
        m_settingpanel_ctrl_btn->move(m_settingpanel_ctrl_btn->pos().x() + 1, m_settingpanel_ctrl_btn->pos().y());
        if(m_settingpanel->x() == 0)
        {
            m_settingpanel_ctrl_btn->setText("隐藏");
            b_settingpanel_visible = true;
            settingpanel_timer.stop();
        }
    }
}

void MainWindow::on_localpanel_timeout()
{
    if(b_localpanel_visible)
    {
        m_localpanel->move(m_localpanel->pos().x(), m_localpanel->pos().y() + 1);
        if(m_localpanel->y() == GetSystemMetrics(SM_CYSCREEN))
        {
            m_localpanel_ctrl_btn->setText("显示");
            b_localpanel_visible = false;
            localpanel_timer.stop();
        }
    }
    else
    {
        m_localpanel->move(m_localpanel->pos().x(), m_localpanel->pos().y() - 1);
        if(m_localpanel->y() == GetSystemMetrics(SM_CYSCREEN) - 70)
        {
            m_localpanel_ctrl_btn->setText("隐藏");
            b_localpanel_visible = true;
            localpanel_timer.stop();
        }
    }
}

void MainWindow::on_usbpanel_timeout()
{
    if(b_usbpanel_visible)
    {
        m_usbpanel->move(m_usbpanel->pos().x(), m_usbpanel->pos().y() - 1);
        if(m_usbpanel->y() + m_usbpanel->height() == 0)
        {
            m_usbpanel_ctrl_btn->setText("显示");
            b_usbpanel_visible = false;
            usbpanel_timer.stop();
        }
    }
    else
    {
        m_usbpanel->move(m_usbpanel->pos().x(), m_usbpanel->pos().y() + 1);
        if(m_usbpanel->y() == 0)
        {
            m_usbpanel_ctrl_btn->setText("隐藏");
            b_usbpanel_visible = true;
            usbpanel_timer.stop();
        }
    }
}
