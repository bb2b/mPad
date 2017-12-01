#ifndef SWITCHBOARD_H
#define SWITCHBOARD_H

#include <QWidget>
#include <QTimer>
#include <QTimerEvent>

namespace Ui {
class SwitchBoard;
}

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
    Ui::SwitchBoard *ui;
    QTimer move_timer;
    bool b_move_direction;  //true表示向下，false表示向上
};

#endif // SWITCHBOARD_H
