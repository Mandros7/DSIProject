#include "Regulador.h"

Regulador::Regulador(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum,
                     double* coefDen, int tam, Conversor *c, Sensor *s, int channel) :
    FDT(entrada,salida,salidasTabla,coefNum,coefDen,tam){
    conv = c;
    sens = s;
    chan = channel;
}

double Regulador::read() {
    short value = sens->getValue();
    pthread_mutex_t m = conv->getMutex();
    pthread_cond_t finished = conv->getFinishCond();
    pthread_mutex_lock(&m);
    double reg = conv->getRegistroControl();
    while(reg>0) {
        pthread_cond_wait(&finished,&m);
        double reg = conv->getRegistroControl();
    }

    conv->setRegistroControl(chan);
    conv->convert(value);
    // Otra espera condicionada aqui?
    double salida = conv->getRegistroDatos();
    conv->setRegistroControl(0);
    pthread_cond_signal(&finished);
    pthread_mutex_unlock(&m);


    return (m_entrada->getValor()[0] - salida);
}
