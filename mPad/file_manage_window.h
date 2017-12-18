#ifndef FILEMANAGEWINDOW_H
#define FILEMANAGEWINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "file.h"
#include "global.h"

class FileManageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FileManageWindow(FilterType filtertype, QString directory, QWidget *parent = 0);
    ~FileManageWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public slots:
    void on_return_button_clicked();
    void on_manage_button_clicked();
    void on_close_button_clicked();

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
    QWidget *m_title_area;
    QWidget *m_files_area;
    QVBoxLayout *m_vlayout;
    QHBoxLayout *m_hlayout;

    bool b_move;
    QPoint m_last_point;
};

#endif // FILEMANAGEWINDOW_H
