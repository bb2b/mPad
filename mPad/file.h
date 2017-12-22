#ifndef FILE_H
#define FILE_H

#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QIcon>
#include <QFileInfo>

class File : public QLabel
{
    Q_OBJECT
public:
    explicit File(bool on_window_or_pupup, QFileInfo fileinfo, QWidget *parent = 0);
    ~File();

public:
    QIcon fileIcon(const QString filepath);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    QFileInfo m_fileinfo;

signals:
    void clicked();

private:
    bool b_on_window_or_pupup;
    QLabel *m_icon;
    QLabel *m_large_file_name;
    QLabel *m_tiny_bg;
    QLabel *m_tiny_file_name;
    QLabel *m_tiny_file_description;
    QLabel *m_tiny_file_size;
};

#endif // FILE_H
