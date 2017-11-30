#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>

namespace Ui {
class WhiteBoard;
}

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent = 0);
    ~WhiteBoard();

private:
    Ui::WhiteBoard *ui;
};

#endif // WHITEBOARD_H
