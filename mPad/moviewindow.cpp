#include "moviewindow.h"
#include "global.h"

QVector<QString> MovieWindow::g_movies(0);

MovieWindow::MovieWindow(QString moviepath, QWidget *parent) : QDialog(parent),
    m_moviepath(moviepath)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);

    MovieWindow::g_movies.push_back(m_moviepath);

    m_movie_widget = new QWidget(this);
    m_max_btn = new QPushButton(this);
    m_close_btn = new QPushButton(this);
    m_progress = new QSlider(m_movie_widget);
    m_volume = new QSlider(m_movie_widget);
    m_timer = new QTimer(this);
    m_player_process = new QProcess(this);
    m_player_process->setProcessChannelMode(QProcess::MergedChannels);

    m_max_btn->setText("全屏");
    m_close_btn->setText("关闭");
    m_progress->setStyleSheet("QSlider::groove:horizontal{border: 1px solid #4A708B;\
                              background:#C0C0C0;\
                              height:5px;\
                              border-radius: 1px;\
                              padding-left:-1px;padding-right:-1px;}"

                              "QSlider::sub-page:horizontal {background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #B1B1B1, stop:1 #c4c4c4);\
                              background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #5DCCFF, stop: 1 #1874CD);\
                              border: 1px solid #4A708B;\
                              height: 10px;\
                              border-radius: 2px;}"

                              "QSlider::add-page:horizontal{background: #575757;\
                              border: 0px solid #777;\
                              height: 10px;\
                              border-radius: 2px;}"

                              "QSlider::handle:horizontal{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\
                              width: 11px;\
                              margin-top: -3px;\
                              margin-bottom: -3px;\
                              border-radius: 5px;}"

                              "QSlider::handle:horizontal:hover{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,stop:0.778409 rgba(255, 255, 255, 255));\
                               width: 11px\
                               margin-top: -3px;\
                               margin-bottom: -3px;\
                               border-radius: 5px;}"

                               "QSlider::sub-page:horizontal:disabled {background: #00009C;\
                               border-color: #999;}"

                               "QSlider::add-page:horizontal:disabled {background: #eee;\
                               border-color: #999;}"

                               "QSlider::handle:horizontal:disabled {background: #eee;\
                               border: 1px solid #aaa;\
                               border-radius: 4px;}"
                              );
    m_volume->setStyleSheet("QSlider::groove:horizontal{border: 1px solid #4A708B;\
                            background:#C0C0C0;\
                            height:5px;\
                            border-radius: 1px;\
                            padding-left:-1px;padding-right:-1px;}"

                            "QSlider::sub-page:horizontal {background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #B1B1B1, stop:1 #c4c4c4);\
                            background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #5DCCFF, stop: 1 #1874CD);\
                            border: 1px solid #4A708B;\
                            height: 10px;\
                            border-radius: 2px;}"

                            "QSlider::add-page:horizontal{background: #575757;\
                            border: 0px solid #777;\
                            height: 10px;\
                            border-radius: 2px;}"

                            "QSlider::handle:horizontal{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\
                            width: 11px;\
                            margin-top: -3px;\
                            margin-bottom: -3px;\
                            border-radius: 5px;}"

                            "QSlider::handle:horizontal:hover{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,stop:0.778409 rgba(255, 255, 255, 255));\
                             width: 11px\
                             margin-top: -3px;\
                             margin-bottom: -3px;\
                             border-radius: 5px;}"

                             "QSlider::sub-page:horizontal:disabled {background: #00009C;\
                             border-color: #999;}"

                             "QSlider::add-page:horizontal:disabled {background: #eee;\
                             border-color: #999;}"

                             "QSlider::handle:horizontal:disabled {background: #eee;\
                             border: 1px solid #aaa;\
                             border-radius: 4px;}"
                            );

    connect(m_max_btn, SIGNAL(clicked()), this, SLOT(on_max_btn_clicked()));
    connect(m_close_btn, SIGNAL(clicked()), this, SLOT(on_close_btn_clicked()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timer_out()));
    connect(m_volume, SIGNAL(valueChanged(int)), this, SLOT(on_volume_slider_valueChanged(int)));

    setGeometry(GetSystemMetrics(SM_CXSCREEN)/4, GetSystemMetrics(SM_CYSCREEN)/4, GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2);

    m_timer->start(10);

    QString m_player_path(qApp->applicationDirPath() + "/mplayer/mplayer.exe");
    QStringList args;
    args << "-slave";
    args << "-quiet";
    args << "-zoom";
    args << "-x";
    args << QString::number(GetSystemMetrics(SM_CXSCREEN));
    args << "-y";
    args << QString::number(GetSystemMetrics(SM_CYSCREEN));
    args << "-wid" << QString::number(m_movie_widget->winId());
    args << m_moviepath.replace("/", "\\");

    m_player_process->start(m_player_path, args);
    m_player_process->write(QString("volume %1 2\n").arg(m_volume->value()).toUtf8());
    m_player_process->write("get_time_length\n");
}

MovieWindow::~MovieWindow()
{
    delete m_progress;
    delete m_volume;
    delete m_max_btn;
    delete m_close_btn;
    delete m_movie_widget;
    m_player_process->write("quit\n");
    delete m_player_process;
}

void MovieWindow::mousePressEvent(QMouseEvent *event)
{
    b_move = true;
    m_last_point = event->pos();
}

void MovieWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    setGeometry(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    //m_player_process->write("vo_fullscreen\n");
}

void MovieWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint new_point = this->pos() + event->pos() - m_last_point;
    if(b_move && new_point.x() >= 0 && new_point.x() + this->width() <= GetSystemMetrics(SM_CXSCREEN) && new_point.y() >= 0 && new_point.y() + this->height() <= GetSystemMetrics(SM_CYSCREEN))
    {
        this->move(new_point);
    }
    else
        m_last_point = event->pos();
}

void MovieWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    b_move = false;
}

void MovieWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    m_movie_widget->setGeometry(0, 0, w, h);
    m_close_btn->setGeometry(w-55,0,50,20);
    m_max_btn->setGeometry(w-m_close_btn->width()-5-50, 0, 50, 20);
    m_progress->setGeometry(0, h-20, w*2/3, 20);
    m_volume->setGeometry(m_progress->width(), h-20, w-m_progress->width(), 20);
}

void MovieWindow::on_max_btn_clicked()
{
    setGeometry(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    //m_player_process->write("vo_fullscreen\n");
}

void MovieWindow::on_close_btn_clicked()
{
    m_player_process->write("quit\n");
    MovieWindow::g_movies.removeOne(m_moviepath.replace("\\", "/"));
    this->close();
}

void MovieWindow::on_timer_out()
{
    m_player_process->write("get_time_pos\n");  //获得视频当前时间
    m_player_process->write("get_percent_pos\n");  //获得视频百分比
    m_player_process->write("get_time_length\n");  // 获得视频总时间

    connect(m_player_process, SIGNAL(readyReadStandardOutput()), this, SLOT(on_update_progress_slider()));
}

void MovieWindow::on_update_progress_slider()
{
    while(m_player_process->canReadLine())
    {
        QByteArray b(m_player_process->readLine());

        b.replace(QByteArray("\n"), QByteArray(""));
        QString s(b);

        if (b.startsWith("ANS_LENGTH"))  //输出视频总时间
        {
            int totalTimeNum = s.mid(11).toFloat();  //直接toInt()不成功，不知道原因

            //int totalTimeDec = (int)(totalTimeNum * 10 % 10);
            int totalTimeSec = (int)(totalTimeNum) % 60;  //提取秒
            int totalTimeMin = (int)(totalTimeNum) / 60;  //提取分钟

            QString totalTime = QString("%1:%2").arg(totalTimeMin).arg(totalTimeSec);  //标准格式输出时间

            m_progress->setRange(0,totalTimeNum);
        }
        else if (b.startsWith("ANS_TIME_POSITION"))  //输出视频当前时间
        {
            int currentTimeNum = s.mid(18).toFloat();

            int currentTimeSec = (int)(currentTimeNum) % 60;
            int currentTimeMin = (int)(currentTimeNum) / 60;

            QString currentTime = QString("%1:%2").arg(currentTimeMin).arg(currentTimeSec);

            m_progress->setValue(currentTimeNum);
        }
    }
}

void MovieWindow::on_volume_slider_valueChanged(int value)
{
    m_player_process->write(QString("volume %1 2\n").arg(value).toUtf8());
}
