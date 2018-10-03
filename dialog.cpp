#include "dialog.h"

#include <QChar>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), isLaunched(false), wasLaunched(false), timePassedStorage(0)
{
    mainLayout = new QGridLayout(this);
    timeLine = new QLabel("0:00:00:000", this);
    timeLine->setAlignment(Qt::AlignCenter);
    launchButton = new QPushButton("start", this);
    resetButton = new QPushButton("reset", this);
    mainLayout->addWidget(timeLine,0, 0, 1, 2);
    mainLayout->addWidget(launchButton, 1, 0);
    mainLayout->addWidget(resetButton, 1, 1);
    this->setLayout(mainLayout);

    timeLineUpdateOffset = new QTimer(this);

    connect(timeLineUpdateOffset, SIGNAL(timeout()), this, SLOT(updateTimeLine()));
    connect(launchButton, SIGNAL(pressed()), this, SLOT(launchButtonPressed()));
    connect(resetButton, SIGNAL(pressed()), this, SLOT(resetButtonPressed()));
}

void Dialog::launchButtonPressed()
{
    if (!isLaunched && !wasLaunched) {
        _time.restart();
        timeLineUpdateOffset->start(20);
       this->isLaunched = true;
       this->wasLaunched = true;
       launchButton->setText("pause");
    } else if (isLaunched) {
        timePassedStorage += _time.elapsed();
        timeLineUpdateOffset->stop();
        this->isLaunched = false;
        launchButton->setText("remuse");
    } else if (!isLaunched) {
         _time.start();
         timeLineUpdateOffset->start(20);
        this->isLaunched = true;
        launchButton->setText("pause");
    }
}

void Dialog::resetButtonPressed()
{
    timeLineUpdateOffset->stop();
    this->launchButton->setText("start");
    this->isLaunched = false;
    this->wasLaunched = false;
    this->timePassedStorage = 0;
    this->timeLine->setText("0:00:00:000");
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
    this->timeLine->setText(res);
}

Dialog::~Dialog()
{
}
