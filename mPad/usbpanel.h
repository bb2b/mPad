#ifndef USBPANEL_H
#define USBPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include "mylabel.h"

class UsbPanel : public QWidget
{
    Q_OBJECT
public:
    explicit UsbPanel(QWidget *parent = 0);
    ~UsbPanel();

    void resizeAll();

public slots:
    void on_usb_all_clicked();
    void on_note_files_clicked();
    void on_ppt_files_clicked();
    void on_word_files_clicked();
    void on_excel_files_clicked();
    void on_pdf_files_clicked();
    void on_picture_files_clicked();
    void on_movie_files_clicked();
    void on_other_files_clicked();

private:
    myLabel *m_usb_all;
    myLabel *m_note_files;
    myLabel *m_ppt_files;
    myLabel *m_word_files;
    myLabel *m_excel_files;
    myLabel *m_pdf_files;
    myLabel *m_picture_files;
    myLabel *m_movie_files;
    myLabel *m_other_files;
    myLabel *m_empty_area;
    QHBoxLayout *m_layout;
};

#endif // USBPANEL_H
