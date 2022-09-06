#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    wiringPiSetup();
    pinMode(LED,OUTPUT);
    myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this,SLOT(function1()));
    //myTimer1->start(1000);
    lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
    lcdHome(lcd);
    lcdClear(lcd);
    series=new QLineSeries();


    chart=new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setMin(0);
    chart->axisX()->setMax(20);
    chart->axisY()->setRange(25,35);
    chart->setTitle("Merenje temperature");
    chartView =new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

Dialog::~Dialog()
{
    delete ui;

}

double Dialog::temperatura()//void in the brackets
{
    FILE *ft;
    char tekst[100];
    ft = fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");
    if(ft == NULL)
        return 0;
    int i = 0;
    for(i=0;i<22;i++)
        fscanf(ft, "%s", tekst);
    fclose(ft);

    for(i=0;i<10;i++)
    {
        tekst[i]=tekst[i+2];
    }
    int temp=atoi(tekst);
    double tem=(double)temp/1000;

    return tem;
};

void Dialog::function1()
{
    ///bool x = 0;
    double temp_var = temperatura();
    ceiling=ui->CeilingSlider->value();
    floor=ui->FloorSlider->value();
    ui->lcdNumber_3->display(ceiling);
    ui->lcdNumber_2->display(floor);
    //printf("\n Merenje \tTemp = %.3f\xC2\xB0 C",temperatura());
    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd,"%.3f 'C",temp_var);
    lcdPosition(lcd, 0, 1);
    lcdPrintf(lcd,"th1: %d th2: %d",floor,ceiling);
    ui->lcdNumber->display(temp_var);
            if(temp_var>ceiling)
            {
                x = !x;
                digitalWrite(LED,x);
            }
            else if(temp_var < floor)
            {
                x = !x;
                digitalWrite(LED,x);
            }
            else
            {
                digitalWrite(LED,0);
            }

            if(del)
            {
                del=0;
                t=0;
                series->clear();
            }
            if(t==21)
            {
                t=0;
                series->clear();
            }
      series->append(t,temp_var);
      t++;
      chartView->update();
}


void Dialog::on_pushButton_clicked()
{
     myTimer1->start(1000);
}

void Dialog::on_pushButton_2_clicked()
{
    del = 1;
}
