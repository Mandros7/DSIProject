#ifndef VCOMP_H
#define VCOMP_H

#include <pthread.h>
class VComp {

private:
    pthread_mutex_t mutex;
    double* valor;
    int m_length;

public:
    VComp(double *valor_inicial, int length);

	double* getValor();
    int getLength();

	void setValor(double* n_Valor);
};

#endif //VCOMP_H
