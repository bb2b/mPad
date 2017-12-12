#ifndef SWITCHBOARD_H
#define SWITCHBOARD_H

#include <QWidget>
#include <QTimer>
#include <QTimerEvent>
#include <QPushButton>
#include <QVBoxLayout>

class SwitchBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchBoard(QWidget *parent = 0);
    ~SwitchBoard();

private slots:
    void on_pushButton_clicked();
    void on_move_timer_out();

private:
    QTimer move_timer;
    bool b_move_direction;  //true表示向下，false表示向上
    QPushButton *pushButton;
    QVBoxLayout *vLayout;
};

#endif // SWITCHBOARD_H
