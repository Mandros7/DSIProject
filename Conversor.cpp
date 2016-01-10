#include "Conversor.h"

double Conversor::getRegistroDatos() {
    return registroDatos;
}

RegistroControl Conversor::getRegistroControl() {
    return CSR;
}

void Conversor::convert(short sensValor) {
    //usleep(10000);
    registroDatos = (double)(sensValor*1000.0/500.0/4095.0*10.0);
    CSR.acabarConversion();
    pthread_cond_signal(&convFinished);
}

Conversor::Conversor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&convFinished, NULL);

}
