#ifndef VCOMP_H
#define VCOMP_H

#include <pthread.h>
class VComp {

private:
    pthread_mutex_t mutex;
    double valor;

public:
    VComp(double valor_inicial);

    double getValor();

    void setValor(double n_Valor);
};

#endif //VCOMP_H
