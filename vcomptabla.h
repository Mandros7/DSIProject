#ifndef VCOMPTABLA_H
#define VCOMPTABLA_H

#include <pthread.h>

class VCompTabla
{
private:
    double * values;
    int m_tam;
    pthread_mutex_t mutex;
public:
    VCompTabla(int tam);
    void add(double n_value);
    double* getTabla();
    //int getTam();
};

#endif // VCOMPTABLA_H
