#include "Regulador.h"
#include <unistd.h>

void add_timespec (struct timespec *suma,
                   const struct timespec *sumando1,
                   const struct timespec *sumando2 );

Regulador::Regulador(VComp* kp, VComp* entrada, VComp* salida, double* coefNum,
                     double* coefDen, int tam, Conversor *c, Sensor *s) :
    FDT(entrada,salida,coefNum,coefDen,tam){
    conv = c;
    sens = s;
    periodo.tv_nsec = 2000000;
    periodo.tv_sec = 0;
    m_kp = kp;
}

VComp* Regulador::getKp(){
    return m_kp;
}

VComp* Regulador::getRef(){
    return m_entrada;
}

int Regulador::read(double *resultado, int chan) {
    struct timespec inicio,fin;

    clock_gettime(CLOCK_REALTIME,&inicio);
    add_timespec(&fin,&inicio,&periodo);

    short value = sens->getValue(); //Valor del sensor

    pthread_mutex_lock(&conv->mutex); //Obtenemos recurso

    while(!conv->CSR.conversionAcabada()) {
        pthread_cond_wait(&conv->cond,&conv->mutex);    //Espera condicionada
    }

    conv->CSR.prepararConversion(chan);
    conv->CSR.lanzarConversion();

    conv->convert(value);

    while(!conv->CSR.conversionAcabada()){
        pthread_cond_wait(&conv->convFinished,&conv->mutex);
    }

    if (conv->CSR.error()){
        pthread_cond_signal(&conv->cond);
        pthread_mutex_unlock(&conv->mutex);
        return -1;
    }

    (*resultado) = (conv->getRegistroDatos());

    clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME,&fin,NULL);

    pthread_cond_signal(&conv->cond);
    pthread_mutex_unlock(&conv->mutex);

    return 0;
}


