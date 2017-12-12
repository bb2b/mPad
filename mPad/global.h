#ifndef GLOBAL
#define GLOBAL

#include <windows.h>
#include <QTextCodec>
#include <QColor>
#include <QPixmap>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QStandardPaths>
#include "note_bar.h"
#include "desktop_switch_bar.h"
#include "whiteboard_switch_button.h"
#include "whiteboard.h"
#include "mainwindow.h"
#include "screenshot.h"

// 是否打印调试信息
#define SUPPORT_DBG         1
#define DRAW                1
#define ERASE               2
#define ROAMING             3
#define SELECT              4
#define SELECT_COLOR        QColor(255, 201, 14)
#define LOCALCLEAR_COLOR    QColor(34, 177, 76)

// 打印调试日志
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
extern ScreenShot *g_screenshot;
extern int g_draw_width;
extern QColor g_draw_color;
extern int g_draw_type;

extern void set_window_top_hint(QWidget *widget, HWND hWndlnsertAfter, bool active);
extern void set_window_foreground(QWidget *widget);
extern QString generate_name_by_current_time(); //将当前时间转换成唯一文件名

#endif // GLOBAL

