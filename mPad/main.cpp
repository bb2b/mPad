#include "global.h"

NoteBar *g_notebar = NULL;
PaintToolBar *g_paintbar = NULL;
DesktopSwitchBar *g_desktopswitchbar = NULL;
SwitchBoard *g_switchboard = NULL;
WhiteBoard *g_whiteboard = NULL;
MainWindow *g_mainwindow = NULL;
ScreenShot *g_screenshot = NULL;
UdiskDetect *g_udiskdetect = NULL;
int g_draw_width = 2;
QColor g_draw_color = QColor(255,0,0);
int g_draw_type = DRAW;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    g_udiskdetect = new UdiskDetect;
    a.installNativeEventFilter(g_udiskdetect);

    g_notebar = new NoteBar;
    g_notebar->show();
    g_paintbar = new PaintToolBar;
    g_paintbar->hide();
    g_desktopswitchbar = new DesktopSwitchBar;
    g_desktopswitchbar->show();
    g_switchboard = new SwitchBoard;
    g_switchboard->show();
    g_whiteboard = new WhiteBoard;
    g_whiteboard->show();
    g_mainwindow = new MainWindow;
    g_mainwindow->showFullScreen();
    g_screenshot = new ScreenShot;

    set_window_top_hint(g_notebar, HWND_TOPMOST, true);
    set_window_top_hint(g_paintbar, HWND_TOPMOST, true);
    set_window_top_hint(g_desktopswitchbar, HWND_TOPMOST, true);
    set_window_top_hint(g_switchboard, HWND_TOPMOST, true);

    return a.exec();
}
