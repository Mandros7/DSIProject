#ifndef VCompGrafica_H
#define VCompGrafica_H

#include <pthread.h>
#include <QObject>

class VCompGrafica : public QObject
{
    Q_OBJECT

private:
    double * valuesYk;
    double * valuesUk;
    int m_tam;
    pthread_mutex_t mutex;
public:
    VCompGrafica(QObject *parent, int tam);
    void add(double UkValue, double YkValue, double tiempo, double ref1);
    double* getTablaYk();
    double* getTablaUk();
    ~VCompGrafica();
    //int getTam();
signals:
    void sendValue(double tiempo, double ref, double yk);
};

#endif // VCOMPTABLA_H
