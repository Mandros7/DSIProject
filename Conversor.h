#ifndef CONVERSOR_H
#define CONVERSOR_H

#include "VComp.h"
#include <pthread.h>
#include <RegistroControl.h>


class Conversor {

private:
    double registroDatos;

public:
    double getRegistroDatos();
    RegistroControl getRegistroControl();
    void setRegistroControl(double channel);
    void convert(short sensValor);
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_cond_t convFinished;
    Conversor();
    RegistroControl CSR;

};

#endif //CONVERSOR_H
