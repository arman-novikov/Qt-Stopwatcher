#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    QGridLayout *mainLayout;
    QLabel      *timeLine;
    QPushButton *launchButton, *resetButton;
    bool isLaunched, wasLaunched;
    QTime _time;
    QTimer *timeLineUpdateOffset;
    qint64 timePassedStorage;
private slots:
    void launchButtonPressed();
    void resetButtonPressed();
    void updateTimeLine();
};

#endif // DIALOG_H
