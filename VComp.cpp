#include "VComp.h"
#include "stdio.h"


/* Variable compartida con un double y un mutex
 * Getters y setters definidos utilizando dicho mutex
 */

VComp::VComp(double valor_inicial) {
    pthread_mutexattr_t atributos;
    pthread_mutexattr_init(&atributos);
    pthread_mutexattr_setprotocol(&atributos,PTHREAD_PRIO_PROTECT);
    valor= valor_inicial;
    pthread_mutex_init(&mutex, &atributos);
}

double VComp::getValor() {
    double result;
    pthread_mutex_lock(&mutex);
    result = valor;
    pthread_mutex_unlock(&mutex);
    return result;
}

void VComp::setValor(double n_Valor) {
    pthread_mutex_lock(&mutex);
    valor = n_Valor;
    pthread_mutex_unlock(&mutex);
}
