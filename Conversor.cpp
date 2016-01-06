#include "Conversor.h"

double Conversor::getRegistroDatos() {
    return this->registroDatos;
}

double Conversor::getRegistroControl() {
    return this->registroControl;
}

void Conversor::setRegistroControl(double channel) {
    registroControl = channel;
}

void Conversor::convert(short sensValor) {
    //usleep(10000);
    registroDatos = (double)(sensValor*1000.0/500.0/4095.0*10.0);
}

Conversor::Conversor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    registroDatos = 0;
    registroControl = 0;
}
