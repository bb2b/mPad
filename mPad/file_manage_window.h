#ifndef FILEMANAGEWINDOW_H
#define FILEMANAGEWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "file.h"

class FileManageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FileManageWindow(QString directory, QWidget *parent = 0);
    ~FileManageWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QString original_directory;
    QString current_directory;
    QVector<QString> directories;
    QLabel *m_directory_label;
    QPushButton *m_return_button;
    QPushButton *m_manage_button;
    QPushButton *m_close_button;
    QWidget *m_manage_area;
    QPushButton *m_generate_pdf_button;
    QPushButton *m_send_button;
    QPushButton *m_save_button;
    QPushButton *m_delete_button;
    QPushButton *m_print_button;
    QPushButton *m_share_button;
    QLabel *m_share_label;
    QScrollArea *m_scrollarea;
};

#endif // FILEMANAGEWINDOW_H
