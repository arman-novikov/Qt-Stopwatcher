#include "dialog.h"

#include <QChar>
#include <QPalette>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), timePassedStorage(0), isLaunched(false), wasLaunched(false)
{
    timeLine = new QLabel("00:00:00:000", this);
    timeLine->setAlignment(Qt::AlignCenter);
    setTimeLineColor(Qt::darkGreen);

    launchButton = new QPushButton("start", this);
    resetButton = new QPushButton("reset", this);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(timeLine,0, 0, 1, 2);
    mainLayout->addWidget(launchButton, 1, 0);
    mainLayout->addWidget(resetButton, 1, 1);
    setLayout(mainLayout);

    timeLineUpdateOffset = new QTimer(this);

    connect(timeLineUpdateOffset, SIGNAL(timeout()), this, SLOT(updateTimeLine()));
    connect(launchButton, SIGNAL(pressed()), this, SLOT(launchButtonPressed()));
    connect(resetButton, SIGNAL(pressed()), this, SLOT(resetButtonPressed()));
}

void Dialog::launchButtonPressed()
{
    if (!wasLaunched) {
        _time.restart();
        timeLineUpdateOffset->start(20);
       isLaunched = true;
       wasLaunched = true;
       setTimeLineColor(Qt::darkRed);
       launchButton->setText("pause");
    } else if (isLaunched) {
        timePassedStorage += _time.elapsed();
        timeLineUpdateOffset->stop();
        isLaunched = false;
        launchButton->setText("remuse");
        setTimeLineColor(Qt::darkYellow);
    } else if (!isLaunched) {
         _time.start();
         timeLineUpdateOffset->start(20);
        isLaunched = true;
        launchButton->setText("pause");
        setTimeLineColor(Qt::darkRed);
    }
}

void Dialog::resetButtonPressed()
{
    timeLineUpdateOffset->stop();
    launchButton->setText("start");
    isLaunched = false;
    wasLaunched = false;
    timePassedStorage = 0;
    timeLine->setText("00:00:00:000");
    setTimeLineColor(Qt::darkGreen);
}

void Dialog::updateTimeLine()
{
    qint64 timePassed = _time.elapsed() + timePassedStorage;
    qint64 hours = timePassed / 1000 / 60 / 60;
    qint64 minutes = (timePassed / 1000 / 60) - (hours * 60);
    qint64 seconds = (timePassed / 1000) - (minutes * 60) - (hours * 3600);
    qint64 mseconds = timePassed % 1000;

    QString res = QString("%1:%2:%3:%4")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'))
            .arg(mseconds, 3, 10, QChar('0'));
    timeLine->setText(res);
}

template <typename Color>
void Dialog::setTimeLineColor(const Color &c)
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, c);
    timeLine->setPalette(palette);
}

Dialog::~Dialog()
{
}
