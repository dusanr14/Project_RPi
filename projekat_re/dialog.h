#ifndef DIALOG_H
#define DIALOG_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE
#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include<QTimer>
#include <lcd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QTimer *myTimer1;
private slots:
    double temperatura();//void in the brackets
    void function1();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    char LED = 25; //maybe public
    int ceiling;
    int floor;
    bool x = 0;
    const int RS = 3;
    const int EN = 14;
    const int D0 = 4;
    const int D1 = 12;
    const int D2 = 13;
    const int D3 = 6;
    int t = 0;
    int del = 0;
    int lcd;
};
#endif // DIALOG_H
