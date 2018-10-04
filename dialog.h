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
    template<typename Color>
        void setTimeLineColor(const Color &c);
    QGridLayout *mainLayout;
    QLabel      *timeLine;
    QPushButton *launchButton, *resetButton;
    QTimer *timeLineUpdateOffset;
    QTime _time;
    qint64 timePassedStorage;
    bool isLaunched, wasLaunched;
private slots:
    void launchButtonPressed();
    void resetButtonPressed();
    void updateTimeLine();
};

#endif // DIALOG_H
