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

private:
    Ui::NoteBar *ui;
};

#endif // NOTEBAR_H
