#ifndef VCOMPTABLA_H
#define VCOMPTABLA_H

#include <pthread.h>
#include <QObject>

class VCompTabla : public QObject
{
    Q_OBJECT

private:
    double * values;
    int m_tam;
    pthread_mutex_t mutex;
public:
    VCompTabla(QObject *parent, int tam);
    void add(double n_value,double tiempo, double ref1);
    double* getTabla();
    ~VCompTabla();
    //int getTam();
signals:
    void sendValue(double tiempo, double ref, double yk);
};

#endif // VCOMPTABLA_H
