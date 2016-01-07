#include "Regulador.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Regulador::Regulador(VComp* kp, VComp* entrada, VComp* salida, double* coefNum,
                     double* coefDen, int tam, Conversor *c, Sensor *s, int channel) :
    FDT(kp,entrada,salida,coefNum,coefDen,tam){
    conv = c;
    sens = s;
    chan = channel;
}

double Regulador::read() {
    //cout<<"Regulador: "<<chan<<endl;
    short value = sens->getValue(); //Valor del sensor

    pthread_mutex_lock(&conv->mutex); //Obtenemos recurso
    double reg = conv->getRegistroControl();

    while(reg!=0 && reg!=chan) {
        //cout<<"Hilo "<<chan<<" esperando por hilo: "<<reg<<endl;
        pthread_cond_wait(&conv->cond,&conv->mutex);    //Espera condicionada
        reg = conv->getRegistroControl();
    }
    //cout<<"Hilo "<<chan<<" accediendo"<<endl;
    conv->setRegistroControl(chan);
    pthread_mutex_unlock(&conv->mutex);

    conv->convert(value);
    double salidaConversor = conv->getRegistroDatos();

    pthread_mutex_lock(&conv->mutex);
    conv->setRegistroControl(0);


    pthread_cond_signal(&conv->cond);
    //cout<<"Hilo "<<chan<<" liberando"<<endl;
    pthread_mutex_unlock(&conv->mutex);

    //usleep(1000000);

    return (m_entrada->getValor() - salidaConversor);
}
