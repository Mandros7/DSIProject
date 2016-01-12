#include "VComp.h"
#include "stdio.h"


/* Variable compartida con un double y un mutex
 * Getters y setters definidos utilizando dicho mutex
 */

VComp::VComp(double valor_inicial) {
    valor= valor_inicial;
    pthread_mutex_init(&mutex, NULL);
}

double VComp::getValor() {
    double result;
    pthread_mutex_lock(&mutex);
    result = valor;
    pthread_mutex_unlock(&mutex);
    return result;
}

void VComp::setValor(double n_Valor) {

    valor = n_Valor;
    pthread_mutex_unlock(&mutex);
}
