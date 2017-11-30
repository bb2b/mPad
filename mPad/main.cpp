#include "global.h"
#include <QApplication>

NoteBar *g_notebar = NULL;
Panel *g_panel = NULL;
SwitchBoard *g_switchboard = NULL;
WhiteBoard *g_whiteboard = NULL;
MainWindow *g_mainwindow = NULL;

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
    g_mainwindow = new MainWindow;
    g_mainwindow->show();

    return a.exec();
}
