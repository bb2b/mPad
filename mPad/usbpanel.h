#ifndef USBPANEL_H
#define USBPANEL_H

#include <QWidget>

class UsbPanel : public QWidget
{
    Q_OBJECT
public:
    explicit UsbPanel(QWidget *parent = 0);
    ~UsbPanel();

public slots:
};

#endif // USBPANEL_H
