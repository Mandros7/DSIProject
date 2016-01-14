#include "Conversor.h"

double Conversor::getRegistroDatos() {
    return registroDatos;
}

RegistroControl Conversor::getRegistroControl() {
    return CSR;
}

// Función de conversión que señaliza el fin mediante la variables de condición.
void Conversor::convert(short sensValor) {
    registroDatos = (double)(sensValor*1000.0/500.0/4095.0*20.0);
    CSR.acabarConversion();
    pthread_cond_signal(&convFinished);
}

// Inicialización de variables en el constructor
Conversor::Conversor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&convFinished, NULL);
}
