#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>
class tank{
private:
    int Level=0,max_level=20000;
    int Q_in=0,Q_out=0;
public:
    void set_level(){
        Level=Level+Q_in-Q_out;
        if(Level>max_level)
                Level=max_level;
        if(Level<0)
            Level=0;
    }
    int GetLevel(){return Level;}
    void set_in(int value){Q_in=value;}
    void set_out(int value){Q_out=value;}
    void set_max(int value){max_level=value;}
};
    tank a;
class valve{
private:
    int output=0,input=0; //Output=valor del dial, Input=nivel del tanque
public:
    void set_in(int value,int refresh){input=value*refresh/1000;}
    void set_out(int dial){
        output=input*(dial/10);
    }
    int get_in(){return input;}
    int get_out(){return output;}




};
valve upstream,dowstream;
 QTimer *play=new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->PauseButton, SIGNAL(clicked()),this,SLOT(Run_or_Stop()));
    connect(ui->time_interval, SIGNAL(valueChanged(int)),this,SLOT(set_timer()));
    connect(play,SIGNAL(timeout()),this,SLOT(tank_flow()));
    connect(ui->tank_volume,SIGNAL(valueChanged(int)),this,SLOT(tank_size()));
    connect(ui->reset,SIGNAL(clicked(bool)),ui->tank,SLOT(reset()));

}
void MainWindow:: tank_size()
{
    int value=10*ui->tank_volume->value();
    qDebug()<<"Tank size changed";
    ui->tank->setMaximum(value);
    a.set_max(value);
}
void MainWindow:: tank_flow(){

    valve V1,V2;
    V1.set_in(ui->Upstream->value(),k);
    V2.set_in(ui->Downstream->value(),k);
    V1.set_out(ui->V1->sliderPosition());
    V2.set_out(ui->V2->sliderPosition());
    a.set_in(V1.get_out());
    a.set_out(V2.get_out());
    a.set_level();
    ui->tank->setValue(a.GetLevel());
    qDebug()<<"Tank_Flow Slot invoked";
}
void MainWindow::Run_or_Stop()
{

    qDebug()<<"Run/Stop Invoked";
    if(play->isActive())
    {
        play->stop();
    }
    else
    {
        play->start(k);
    }
}
void MainWindow:: set_timer(){

        qDebug()<<"Timer inicializado";
        k=ui->time_interval->value();
        play->setInterval(k);

    }
MainWindow::~MainWindow()
{
    delete ui;
}


