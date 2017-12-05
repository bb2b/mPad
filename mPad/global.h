#ifndef GLOBAL
#define GLOBAL

#include <windows.h>
#include <QTextCodec>
#include "notebar.h"
#include "panel.h"
#include "switchboard.h"
#include "whiteboard.h"
#include "mainwindow.h"

// �Ƿ��ӡ������Ϣ
#define SUPPORT_DBG        1

// ��ӡ������־
static inline void WriteLog(const char* format, ...)
{
    char szBuf[1024] = { 0 };
    va_list arg = NULL;

    va_start(arg, format);
    vsprintf_s(szBuf, sizeof(szBuf), format, arg);
    va_end(arg);

    OutputDebugStringA(szBuf);
    return;
}
#if SUPPORT_DBG
#define WRITE_LOG(fmt, ...) WriteLog(fmt, ##__VA_ARGS__)
#else
#define WRITE_LOG(fmt, ...)
#endif

extern NoteBar *g_notebar;
extern Panel *g_panel;
extern SwitchBoard *g_switchboard;
extern WhiteBoard *g_whiteboard;
extern MainWindow *g_mainwindow;

extern void set_window_top_hint(QWidget *widget, HWND hWndlnsertAfter, bool active);
extern void set_window_foreground(QWidget *widget);

#endif // GLOBAL

