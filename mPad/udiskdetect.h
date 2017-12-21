#ifndef UDISKDETECT_H
#define UDISKDETECT_H

#include <QWidget>
#include <QAbstractNativeEventFilter>
#include <windows.h>
#include <dbt.h>

class UdiskDetect : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

signals:
    void sigUDiskCome(QString uDiskName);
    void sigUDiskRemove();

private:
    char FirstDriveFromMask(ULONG unitmask);
};

#endif // UDISKDETECT_H
