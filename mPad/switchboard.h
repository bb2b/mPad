#ifndef SWITCHBOARD_H
#define SWITCHBOARD_H

#include <QWidget>

namespace Ui {
class SwitchBoard;
}

class SwitchBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchBoard(QWidget *parent = 0);
    ~SwitchBoard();

private:
    Ui::SwitchBoard *ui;
};

#endif // SWITCHBOARD_H
