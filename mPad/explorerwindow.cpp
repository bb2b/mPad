#include "explorerwindow.h"
#include "global.h"

QVector<QString> ExplorerWindow::g_files(0);

ExplorerWindow::ExplorerWindow(QString filepath, QWidget *parent) : QWidget(parent),
    n_current_page(0)
{
    ExplorerWindow::g_files.push_back(filepath);
    m_display = new QLabel(this);
    m_max_btn = new QPushButton(m_display);
    m_open_on_desktop_btn = new QPushButton(m_display);
    m_previous_page_left_btn = new QPushButton(m_display);
    m_previous_page_right_btn = new QPushButton(m_display);
    m_previous_page_left_btn->setEnabled(false);
    m_previous_page_right_btn->setEnabled(false);
    m_next_page_left_btn = new QPushButton(m_display);
    m_next_page_right_btn = new QPushButton(m_display);
    m_max_btn->setText("全屏");
    m_open_on_desktop_btn->setText("在外部打开");
    m_previous_page_left_btn->setText("上一页");
    m_previous_page_right_btn->setText("上一页");
    m_next_page_left_btn->setText("下一页");
    m_next_page_right_btn->setText("下一页");

    m_pdf = new PdfUtils(filepath);
    if(m_pdf->getNumPages() > 0)
    {
        m_next_page_left_btn->setEnabled(true);
        m_next_page_right_btn->setEnabled(true);
    }
    else
    {
        m_next_page_left_btn->setEnabled(false);
        m_next_page_right_btn->setEnabled(false);
    }

    connect(m_max_btn, SIGNAL(clicked()), this, SLOT(on_max_btn_clicked()));
    connect(m_open_on_desktop_btn, SIGNAL(clicked()), this, SLOT(on_open_on_desktop_btn_clicked()));
    connect(m_previous_page_left_btn, SIGNAL(clicked()), this, SLOT(on_previous_page_btn_clicked()));
    connect(m_previous_page_right_btn, SIGNAL(clicked()), this, SLOT(on_previous_page_btn_clicked()));
    connect(m_next_page_left_btn, SIGNAL(clicked()), this, SLOT(on_next_page_btn_clicked()));
    connect(m_next_page_right_btn, SIGNAL(clicked()), this, SLOT(on_next_page_btn_clicked()));

    int h = GetSystemMetrics(SM_CYSCREEN) / 2;
    int w = m_pdf->getPageSize().width() * h / m_pdf->getPageSize().height();
    setGeometry((GetSystemMetrics(SM_CXSCREEN) - w)/2, (GetSystemMetrics(SM_CYSCREEN) - h)/2, w, h);
}

ExplorerWindow::~ExplorerWindow()
{
    delete m_max_btn;
    delete m_open_on_desktop_btn;
    delete m_previous_page_left_btn;
    delete m_previous_page_right_btn;
    delete m_next_page_left_btn;
    delete m_next_page_right_btn;
    delete m_display;
    delete m_pdf;
}

void ExplorerWindow::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
}

void ExplorerWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    int h = GetSystemMetrics(SM_CYSCREEN);
    int w = m_pdf->getPageSize().width() * h / m_pdf->getPageSize().height();
    this->setGeometry((GetSystemMetrics(SM_CXSCREEN) - w)/2, (GetSystemMetrics(SM_CYSCREEN) - h)/2, w, h);
}

void ExplorerWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint new_point = this->pos() + event->pos() - m_last_point;
    if(b_move && new_point.x() >= 0 && new_point.x() + this->width() <= GetSystemMetrics(SM_CXSCREEN) && new_point.y() >= 0 && new_point.y() + this->height() <= GetSystemMetrics(SM_CYSCREEN))
    {
        this->move(new_point);
    }
    else
        m_last_point = event->pos();
}

void ExplorerWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    b_move = false;
}

void ExplorerWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    m_open_on_desktop_btn->setGeometry(w-65,0,60,20);
    m_max_btn->setGeometry(w-m_open_on_desktop_btn->width()-5-40,0,40,20);
    m_previous_page_left_btn->setGeometry(0,h/3,40,20);
    m_previous_page_right_btn->setGeometry(w-45,h/3,40,20);
    m_next_page_left_btn->setGeometry(0,h*2/3,40,20);
    m_next_page_right_btn->setGeometry(w-45,h*2/3,40,20);
    m_display->setGeometry(0,0,w,h);
    m_display->setPixmap(QPixmap::fromImage(m_pdf->getPdfImage(n_current_page,m_display->width(),m_display->height())));
}

void ExplorerWindow::on_max_btn_clicked()
{

}

void ExplorerWindow::on_open_on_desktop_btn_clicked()
{

}

void ExplorerWindow::on_previous_page_btn_clicked()
{
    n_current_page--;
    m_display->setPixmap(QPixmap::fromImage(m_pdf->getPdfImage(n_current_page,m_display->width(),m_display->height())));
    if(n_current_page == 0)
    {
        m_previous_page_left_btn->setEnabled(false);
        m_previous_page_right_btn->setEnabled(false);
        if(m_pdf->getNumPages() > 0)
        {
            m_next_page_left_btn->setEnabled(true);
            m_next_page_right_btn->setEnabled(true);
        }
    }
}

void ExplorerWindow::on_next_page_btn_clicked()
{
    n_current_page++;
    m_display->setPixmap(QPixmap::fromImage(m_pdf->getPdfImage(n_current_page,m_display->width(),m_display->height())));
    if(n_current_page == 1)
    {
        m_previous_page_left_btn->setEnabled(true);
        m_previous_page_right_btn->setEnabled(true);
    }
    if(n_current_page == m_pdf->getNumPages() - 1)
    {
        m_next_page_left_btn->setEnabled(false);
        m_next_page_right_btn->setEnabled(false);
    }
}
