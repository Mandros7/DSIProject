#include "Regulador.h"
#include <unistd.h>

Regulador::Regulador(VComp* kp, VComp* entrada, VComp* salida, double* coefNum,
                     double* coefDen, int tam, Conversor *c, Sensor *s, int channel) :
    FDT(kp,entrada,salida,coefNum,coefDen,tam){
    conv = c;
    sens = s;
    chan = channel;
}

double Regulador::read() {
    short value = sens->getValue(); //Valor del sensor
    pthread_mutex_lock(&conv->mutex); //Obtenemos recurso
    double reg = conv->getRegistroControl();

    while(reg!=0 && reg!=chan) {
        pthread_cond_wait(&conv->cond,&conv->mutex);    //Espera condicionada
        reg = conv->getRegistroControl();
    }
    conv->setRegistroControl(chan);
    pthread_mutex_unlock(&conv->mutex);

    conv->convert(value);
    double salidaConversor = conv->getRegistroDatos();

    pthread_mutex_lock(&conv->mutex);
    conv->setRegistroControl(0);
    pthread_cond_signal(&conv->cond);
    pthread_mutex_unlock(&conv->mutex);

    return (m_entrada->getValor() - salidaConversor);
}
