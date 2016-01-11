#include "gui.h"
#include "ui_gui.h"
#include "VComp.h"
#include "VCompGrafica.h"
#include <graf.h>

extern VComp kp1;
extern VComp ref1;
extern VCompGrafica TablaSalidas1;
extern VComp kp2;
extern VComp ref2;
extern VCompGrafica TablaSalidas2;
extern bool running;


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);


    connect(ui->cambiarKp1Button,SIGNAL(clicked()),this,SLOT(setKp1()));
    connect(ui->cambiarRef1Button,SIGNAL(clicked()),this,SLOT(setRef1()));
    connect(ui->updateButton,SIGNAL(clicked()),this,SLOT(actualizarTablasLazo1()));
    connect(ui->cambiaKp2Button,SIGNAL(clicked()),this,SLOT(setKp2()));
    connect(ui->cambiaRef2Button,SIGNAL(clicked()),this,SLOT(setRef2()));
    connect(ui->update2Button,SIGNAL(clicked()),this,SLOT(actualizarTablasLazo2()));

    ui->tableWidget->setHorizontalHeaderLabels(QString("t;t-1;t-2;t-3;t-4").split(";"));
    ui->tableWidget->setVerticalHeaderLabels(QString("Yk;Uk").split(";"));
    ui->tableWidget2->setHorizontalHeaderLabels(QString("t;t-1;t-2;t-3;t-4").split(";"));
    ui->tableWidget2->setVerticalHeaderLabels(QString("Yk;Uk").split(";"));

    ui->VActualKp1->setText(QString::number(kp1.getValor()));
    ui->VActualRef1->setText(QString::number(ref1.getValor()));
    ui->VActualKp2->setText(QString::number(kp2.getValor()));
    ui->VActualRef2->setText(QString::number(ref2.getValor()));
}

GUI::~GUI()
{
    running = false;
    delete ui;
}

void GUI::setRef1()
{
    double value = ui->ref1Input->text().toDouble();
    if (value<0){
        value = 0;
    }
    if (value>10){
        value = 10;
    }
    ref1.setValor(value);
    ui->VActualRef1->setText(QString::number(value));
    ui->ref1Input->clear();
}

void GUI::setKp1()
{
    double value = ui->kp1Input->text().toDouble();
    if (value<0){
        value = 0;
    }
    if (value>10){
        value = 10;
    }
    kp1.setValor(value);
    ui->VActualKp1->setText(QString::number(value));
    ui->kp1Input->clear();
}

void GUI::actualizarTablasLazo1(){
    double * tablasYk = TablaSalidas1.getTablaYk();
    double * tablasUk = TablaSalidas1.getTablaUk();
    for (int i=0; i<5;i++){
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(QString("%1").arg(tablasYk[i])));
        ui->tableWidget->setItem(1,i,new QTableWidgetItem(QString("%1").arg(tablasUk[i])));
    }
}

void GUI::setRef2()
{
    double value = ui->ref2Input->text().toDouble();
    if (value<0){
        value = 0;
    }
    if (value>10){
        value = 10;
    }
    ref2.setValor(value);
    ui->VActualRef2->setText(QString::number(value));
    ui->ref2Input->clear();
}

void GUI::setKp2()
{
    double value = ui->kp2Input->text().toDouble();
    if (value<0){
        value = 0;
    }
    if (value>10){
        value = 10;
    }
    kp2.setValor(value);
    ui->VActualKp2->setText(QString::number(value));
    ui->kp2Input->clear();
}

void GUI::actualizarTablasLazo2(){
    double * tablasYk = TablaSalidas2.getTablaYk();
    double * tablasUk = TablaSalidas2.getTablaUk();
    for (int i=0; i<5;i++){
        ui->tableWidget2->setItem(0,i,new QTableWidgetItem(QString("%1").arg(tablasYk[i])));
        ui->tableWidget2->setItem(1,i,new QTableWidgetItem(QString("%1").arg(tablasUk[i])));
    }
}
