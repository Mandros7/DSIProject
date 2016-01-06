#ifndef CONVERSOR_H
#define CONVERSOR_H

#include "VComp.h"
#include <pthread.h>


class Conversor {

private:
    double registroDatos;
    double registroControl;


public:
    double getRegistroDatos();
    double getRegistroControl();
    void setRegistroControl(double channel);
    void convert(short sensValor);
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Conversor();
};

#endif //CONVERSOR_H
