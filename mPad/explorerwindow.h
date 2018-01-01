#ifndef EXPLORERWINDOW_H
#define EXPLORERWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QVector>
#include <QFileInfo>

class ExplorerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ExplorerWindow(QString filepath, QWidget *parent = 0);
    ~ExplorerWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    static QVector<QString> g_files;

private:
    bool b_move;
    QPoint m_last_point;
};

#endif // EXPLORERWINDOW_H
