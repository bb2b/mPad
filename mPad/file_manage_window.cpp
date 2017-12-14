#include "file_manage_window.h"
#include "global.h"
#include <QGroupBox>

FileManageWindow::FileManageWindow(QString directory, QWidget *parent) : QWidget(parent)
{
    original_directory = directory;

    m_directory_label = new QLabel(this);
    m_directory_label->setText(original_directory);
    m_return_button = new QPushButton(this);
    m_return_button->setText("����");
    m_manage_button = new QPushButton(this);
    m_manage_button->setText("�ļ�����");
    m_close_button = new QPushButton(this);
    m_close_button->setText("�ر�");

    m_manage_area = new QWidget(this);
    m_manage_area->setStyleSheet("QWidget{background-color:gray;}");
    m_generate_pdf_button = new QPushButton(m_manage_area);
    m_generate_pdf_button->setText("����pdf");
    m_send_button = new QPushButton(m_manage_area);
    m_send_button->setText("��Ϊ��������");
    m_save_button = new QPushButton(m_manage_area);
    m_save_button->setText("�浽U��");
    m_delete_button = new QPushButton(m_manage_area);
    m_delete_button->setText("ɾ��");
    m_print_button = new QPushButton(m_manage_area);
    m_print_button->setText("��ӡ");
    m_share_button = new QPushButton(m_manage_area);
    m_share_button->setText("ɨ�����");

    m_share_label = new QPushButton(this);
    m_scrollarea = new QScrollArea(this);

    QGroupBox groupbox = new QGroupBox(m_scrollarea);
    groupbox.setStyleSheet(""
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
}

FileManageWindow::~FileManageWindow()
{
    delete m_directory_label;
    delete m_return_button;
    delete m_manage_button;
    delete m_close_button;
    delete m_manage_area;
    delete m_generate_pdf_button;
    delete m_send_button;
    delete m_save_button;
    delete m_delete_button;
    delete m_print_button;
    delete m_share_button;
    delete m_share_label;
    delete m_scrollarea;
}

void FileManageWindow::mousePressEvent(QMouseEvent *event)
{

}

void FileManageWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void FileManageWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void FileManageWindow::resizeEvent(QResizeEvent *event)
{
    int h = event->size().height();
    int w = event->size().width();
}
