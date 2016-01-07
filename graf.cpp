#include "graf.h"
#include "qcustomplot.h"
#include <stdlib.h>

Graf::Graf(QCustomPlot *ptr,QObject *parent ): QObject(parent)
{
    dib= ptr;
    setupRealTimeData(dib);
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
    customPlot->graph(0)->setName("Entrada ");
    customPlot->graph(1)->setName("Salida ");
    customPlot->axisRect()->setupFullAxesBox();
}

void Graf:: dataSlot(double tiempo, double ref1, double y1)
{
    static float minAxeY=-1;
    static float maxAxeY=10;
    //if (ref1> maxAxeY) maxAxeY= ref1;
    //if (y1> maxAxeY) maxAxeY= y1;

    //if (ref1 <  minAxeY) minAxeY= ref1;
    //if (y1 < minAxeY) minAxeY= y1;

    // añadir nuevo par de datos al gráfico:

    dib->graph(0)->addData(tiempo, ref1);  // dibujar ref
    if(!(y1!=y1)){
    dib->graph(1)->addData(tiempo, y1);
    }// dibujar salida
    // Sin Reescalado de los ejes, la curva se comprime porque se
    // aumenta la ventana temporal
    // Si se quitan los comentarios la ventana temporal cambia sus límtes
    // pero no su tamaño.La curva se desplaza, aparece por la dcha y se va por la izq.
// /*
    dib->graph(1)->rescaleAxes(true);
    dib->graph(0)->rescaleAxes(true);

    dib->graph(1)->rescaleKeyAxis(true);
    dib->graph(0)->rescaleKeyAxis(true);

    dib->xAxis->setRange(tiempo,10, Qt::AlignRight);
    dib->yAxis->setRange ( minAxeY*1.1,maxAxeY*1.1);
// */
    dib->replot();

}
