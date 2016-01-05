#include "Conversor.h"

double Conversor::getRegistroDatos() {
    return registroDatos;
}

double Conversor::getRegistroControl() {
    return registroControl;
}

void Conversor::setRegistroControl(double channel) {
    registroControl = channel;
}


pthread_mutex_t Conversor::getMutex() {
    return mutex;
}

pthread_cond_t Conversor::getFinishCond() {
    return cond;
}

void Conversor::convert(short sensValor) {
    registroDatos = (double)(sensValor*1000.0/500.0/4095.0*10.0);
}

Conversor::Conversor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    registroDatos = 0;
    registroControl = 0;
}
