#ifndef LOCALPANEL_H
#define LOCALPANEL_H

#include <QLabel>
#include <QHBoxLayout>
#include "mylabel.h"

class LocalPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LocalPanel(QWidget *parent = 0);
    ~LocalPanel();

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
};

#endif // LOCALPANEL_H
