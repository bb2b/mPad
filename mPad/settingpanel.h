#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SettingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SettingPanel(QWidget *parent = 0);
    ~SettingPanel();

public:
    void resizeAll();

public slots:
    void on_setting_btn_clicked();
    void on_eject_btn_clicked();
    void on_about_btn_clicked();
    void on_exit_btn_clicked();

private:
    QPushButton *m_setting;
    QPushButton *m_eject;
    QPushButton *m_about;
    QPushButton *m_exit;
    QVBoxLayout *m_layout;
};

#endif // SETTINGPANEL_H
