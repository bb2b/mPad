#ifndef FILEMANAGEPOPUP_H
#define FILEMANAGEPOPUP_H

#include <QDialog>
#include <QResizeEvent>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QList>
#include "file.h"

class FileManagePopup : public QDialog
{
    Q_OBJECT
public:
    explicit FileManagePopup(int filtertype, QString directory, bool onBottom, bool newHtml = false, QWidget *parent = 0);
    ~FileManagePopup();

public:
    QFileInfoList get_file_list(QString path, QStringList filters);
    QFileInfoList get_file_list_no_filter(QString path);
    QList<QFileInfoList> sort_by_createdtime(QFileInfoList filelist);
    static bool compareCreateTime(const QFileInfo &fileinfo1, const QFileInfo &fileinfo2);

signals:
    void myclose();

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void on_setting_button_clicked();
    void on_close_button_clicked();
    void on_newHtml_button_clicked();

private:
    QString current_directory;
    bool m_onBottom;
    bool m_newHtml;
    int g_filtertype;
    QPushButton *m_setting_button;
    QPushButton *m_close_button;
    QPushButton *m_newHtml_button;
    QScrollArea *m_scrollarea;
    QWidget *m_title_area;
    QWidget *m_files_area;
    QVBoxLayout *m_vlayout;
    QHBoxLayout *m_hlayout;
    QVBoxLayout *m_vspacer;
};

#endif // FILEMANAGEPOPUP_H
