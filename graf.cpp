#include "graf.h"
#include "qcustomplot.h"
#include <stdlib.h>


extern double get_TimeStamp (struct timespec inicio, struct timespec ahora);

Graf::Graf(double secondsBetweenPlot,QCustomPlot *ptr,QObject *parent ): QObject(parent)
{
    dib= ptr;
    setupRealTimeData(dib);
    clock_gettime(CLOCK_REALTIME, &inicio);
    elapsed_time = secondsBetweenPlot;
    minAxeY=-1;
    maxAxeY=10;
}

void Graf::setupRealTimeData(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->xAxis->setLabel("tiempo s");
    customPlot->yAxis->setLabel("Salida rad/s");

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica",9));
    customPlot->graph(0)->setName("Referencia ");
    customPlot->graph(1)->setName("Salida ");
    customPlot->axisRect()->setupFullAxesBox();
}

void Graf:: dataSlot(double tiempo, double ref1, double y1)
{
    clock_gettime(CLOCK_REALTIME, &ahora);
    if (get_TimeStamp(inicio,ahora)>elapsed_time){
        inicio = ahora;


        if (ref1> maxAxeY) maxAxeY= ref1;
        if (y1> maxAxeY) maxAxeY= y1;

        if (ref1 <  minAxeY) minAxeY= ref1;
        if (y1 < minAxeY) minAxeY= y1;

        if(maxAxeY<10) maxAxeY = 10;
        if(minAxeY>-1) minAxeY = 1;

        dib->graph(0)->addData(tiempo, ref1);
        dib->graph(1)->addData(tiempo, y1);

        dib->graph(1)->rescaleAxes(true);
        dib->graph(0)->rescaleAxes(true);

        dib->graph(1)->rescaleKeyAxis(true);
        dib->graph(0)->rescaleKeyAxis(true);

        dib->xAxis->setRange(tiempo,10, Qt::AlignRight);
        dib->yAxis->setRange (minAxeY*1.1,maxAxeY*1.1);

        dib->replot();

        clock_gettime(CLOCK_REALTIME, &tiempoBucle);
        if(get_TimeStamp(ahora,tiempoBucle)>elapsed_time){
            elapsed_time = get_TimeStamp(ahora,tiempoBucle)*1.15;
        }
    }
}
