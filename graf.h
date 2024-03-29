#ifndef GRAF_H
#define GRAF_H
#include <QObject>
#include "qcustomplot.h"

class Graf: public QObject
{
    Q_OBJECT
public:
    Graf(double secondsBetweenPlot,QCustomPlot *ptr,QObject *parent=0 );

    QCustomPlot *dib;
    void setupRealTimeData(QCustomPlot *customPlot);
private:
    struct timespec inicio,ahora,tiempoBucle;
    double elapsed_time;
    double minAxeY;
    double maxAxeY;

public slots:
    void dataSlot(double tiempo, double ref1, double y1);
};

#endif // GRAF_H
