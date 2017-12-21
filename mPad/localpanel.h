#ifndef LOCALPANEL_H
#define LOCALPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include "mylabel.h"
#include "file_manage_window.h"

class LocalPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LocalPanel(QWidget *parent = 0);
    ~LocalPanel();

public:
    void resizeAll();

public slots:
    void on_all_files_clicked();
    void on_note_files_clicked();
    void on_ppt_files_clicked();
    void on_word_files_clicked();
    void on_excel_files_clicked();
    void on_pdf_files_clicked();
    void on_picture_files_clicked();
    void on_movie_files_clicked();
    void on_other_files_clicked();
    void on_html_collect_clicked();
    void on_filemanagewindow_all_close();
    void on_filemanagewindow_note_close();
    void on_filemanagewindow_pic_close();

private:
    myLabel *m_all_files;
    myLabel *m_note_files;
    myLabel *m_ppt_files;
    myLabel *m_word_files;
    myLabel *m_excel_files;
    myLabel *m_pdf_files;
    myLabel *m_picture_files;
    myLabel *m_movie_files;
    myLabel *m_other_files;
    myLabel *m_html_collect;
    myLabel *m_empty_area;
    QHBoxLayout *m_layout;
    FileManageWindow *filemanagewindow_all;
    FileManageWindow *filemanagewindow_note;
    FileManageWindow *filemanagewindow_pic;
};

#endif // LOCALPANEL_H
