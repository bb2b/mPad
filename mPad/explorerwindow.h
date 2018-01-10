#ifndef EXPLORERWINDOW_H
#define EXPLORERWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QVector>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>
#include "pdfutils.h"

class ExplorerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ExplorerWindow(QString realpath, QString filepath, QWidget *parent = 0);
    ~ExplorerWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    static QVector<QString> g_files;

public slots:
    void on_max_btn_clicked();
    void on_open_on_desktop_btn_clicked();
    void on_previous_page_btn_clicked();
    void on_next_page_btn_clicked();
    void on_close_btn_clicked();

private:
    bool b_move;
    int n_current_page;
    QPoint m_last_point;
    QLabel *m_display;
    PdfUtils *m_pdf;
    QPushButton *m_max_btn;
    QPushButton *m_open_on_desktop_btn;
    QPushButton *m_previous_page_left_btn;
    QPushButton *m_previous_page_right_btn;
    QPushButton *m_next_page_left_btn;
    QPushButton *m_next_page_right_btn;
    QPushButton *m_close_btn;
    QString m_realpath;
};

#endif // EXPLORERWINDOW_H
