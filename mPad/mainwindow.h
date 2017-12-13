#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QTimer>
#include "settingpanel.h"
#include "localpanel.h"
#include "usbpanel.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void on_settingpanel_ctrl_btn_clicked();
    void on_localpanel_ctrl_btn_clicked();
    void on_usbpanel_ctrl_btn_clicked();
    void on_settingpanel_timeout();
    void on_localpanel_timeout();
    void on_usbpanel_timeout();

private:
    QPushButton *m_settingpanel_ctrl_btn;
    QPushButton *m_localpanel_ctrl_btn;
    QPushButton *m_usbpanel_ctrl_btn;
    SettingPanel *m_settingpanel;
    LocalPanel *m_localpanel;
    UsbPanel *m_usbpanel;
    bool b_settingpanel_visible;
    bool b_localpanel_visible;
    bool b_usbpanel_visible;
    QTimer settingpanel_timer;
    QTimer localpanel_timer;
    QTimer usbpanel_timer;
};

#endif // MAINWINDOW_H
