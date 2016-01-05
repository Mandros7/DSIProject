#include "VComp.h"

VComp::VComp(double *valor_inicial, int length) {
    valor = valor_inicial;
    m_length = length;
    pthread_mutex_init(mutex, NULL);
}

double* VComp::getValor() {   
    return valor;
}

int VComp::getLength(){
    return m_length;
}

void VComp::setValor(double* n_Valor) {
    pthread_mutex_lock(mutex);
    valor = n_Valor;
    pthread_mutex_unlock(mutex);
}
