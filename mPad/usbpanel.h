#ifndef USBPANEL_H
#define USBPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include "mylabel.h"
#include "file_manage_window.h"
#include "file_manage_popup.h"

class UsbPanel : public QWidget
{
    Q_OBJECT
public:
    explicit UsbPanel(QString UsbName, QWidget *parent = 0);
    ~UsbPanel();

public:
    void resizeAll();
    QString generate_note_folder();
    void delete_all_popup();

public:
    QString m_usbname;

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
    void on_filemanagewindow_all_close();
    void on_filemanagewindow_note_close();
    void on_filemanagewindow_pic_close();
    void on_filemanagepopup_ppt_close();
    void on_filemanagepopup_word_close();
    void on_filemanagepopup_excel_close();
    void on_filemanagepopup_pdf_close();
    void on_filemanagepopup_movie_close();
    void on_filemanagepopup_other_close();

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
    FileManageWindow *filemanagewindow_all;
    FileManageWindow *filemanagewindow_note;
    FileManageWindow *filemanagewindow_pic;
    FileManagePopup *filemanagepopup_ppt;
    FileManagePopup *filemanagepopup_word;
    FileManagePopup *filemanagepopup_excel;
    FileManagePopup *filemanagepopup_pdf;
    FileManagePopup *filemanagepopup_movie;
    FileManagePopup *filemanagepopup_other;
};

#endif // USBPANEL_H
