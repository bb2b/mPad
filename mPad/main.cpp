#include "global.h"
#include <QApplication>

NoteBar *g_notebar = NULL;
Panel *g_panel = NULL;
SwitchBoard *g_switchboard = NULL;
WhiteBoard *g_whiteboard = NULL;
MainWindow *g_mainwindow = NULL;
int g_draw_width = 2;
QColor g_draw_color = QColor(255,0,0);
int g_draw_type = DRAW;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    g_notebar = new NoteBar;
    g_notebar->show();
    g_panel = new Panel;
    g_panel->show();
    g_switchboard = new SwitchBoard;
    g_switchboard->show();
    g_whiteboard = new WhiteBoard;
    g_whiteboard->show();
    g_mainwindow = new MainWindow;
    g_mainwindow->showFullScreen();

    set_window_top_hint(g_notebar, HWND_TOPMOST, true);
    set_window_top_hint(g_panel, HWND_TOPMOST, true);
    set_window_top_hint(g_switchboard, HWND_TOPMOST, true);

    return a.exec();
}
