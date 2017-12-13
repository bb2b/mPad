#ifndef FILE_H
#define FILE_H

#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

class File : public QLabel
{
    Q_OBJECT
public:
    explicit File(bool islarge, QString filepath, QString filename, QString filecreatetime, QString filedescription, int filesize, QWidget *parent = 0);
    ~File();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    QString filePath;
    QString fileName;
    QString fileCreateTime;
    QString fileDescription;
    int fileType;
    int fileSize;

private:
    bool isLargeDisplay;
    QLabel *m_large_file_name;
    QLabel *m_tiny_bg;
    QLabel *m_tiny_file_name;
    QLabel *m_tiny_file_description;
    QLabel *m_tiny_file_size;
};

#endif // FILE_H
