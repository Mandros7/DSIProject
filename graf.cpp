#include "graf.h"
#include "qcustomplot.h"
#include <stdlib.h>

/* Clase que gestiona los objetos de tipo QCustomPlot en los que se realiza un plot de los datos.
 * Dispone de un slot encargado de recibir datos de un objeto VCompGrafica.
 * Se ha introducido un metodo adaptativo que permita la usabilidad maxima posible de la interfaz
 * en casos en los que la ejecucion de slots consuma demasiado tiempo de CPU.
 */

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

        //Metodo adaptativo de actualizacion de graficas en funcion de uso de CPU
        //Permite que la interfaz siga siendo utilizable modificando el tiempo de refresco de las gráficas

        clock_gettime(CLOCK_REALTIME, &tiempoBucle);
        // Si el tiempo de procesado del slot es mayor al periodo de refresco, se aumenta este ultimo en 20%
        if(get_TimeStamp(ahora,tiempoBucle)>elapsed_time){
            elapsed_time = get_TimeStamp(ahora,tiempoBucle)*1.2;
            //cout << elapsed_time << endl;
        }
        // Si el tiempo de procesado disminuye hasta ser 20 veces menor que el periodo, se diminuye el periodo
        if(get_TimeStamp(ahora,tiempoBucle)*20<elapsed_time){
            elapsed_time = get_TimeStamp(ahora,tiempoBucle)*10;
            //cout << elapsed_time << endl;
        }
    }
}
