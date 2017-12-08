#include "global.h"

void set_window_top_hint(QWidget *widget, HWND hWndlnsertAfter, bool active)
{
    if (!SetWindowPos((HWND)widget->winId(), hWndlnsertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE)) {
        WRITE_LOG("SetWindowPos error: %d", GetLastError());
    }

    if (active) {
        if (!SetForegroundWindow((HWND)widget->winId())) {
            WRITE_LOG("SetForegroundWindow error: %d", GetLastError());
        }
    }
}

void set_window_foreground(QWidget *widget)
{
    if (!SetForegroundWindow((HWND)widget->winId())) {
        WRITE_LOG("SetForegroundWindow error: %d", GetLastError());
    }
}

QString generate_name_by_current_time()
{
    QDateTime time = QDateTime::currentDateTime();
    return "\\" + time.toString("yyyyMMddhhmmss") + ".jpg";
}
