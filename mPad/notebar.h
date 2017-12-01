#ifndef NOTEBAR_H
#define NOTEBAR_H

#include <QWidget>

namespace Ui {
class NoteBar;
}

class NoteBar : public QWidget
{
    Q_OBJECT

public:
    explicit NoteBar(QWidget *parent = 0);
    ~NoteBar();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_NoteButton_clicked();

private:
    Ui::NoteBar *ui;
    bool b_move;
    QPoint m_last_point;
};

#endif // NOTEBAR_H
