#include "Regulador.h"
#include <unistd.h>

extern void add_timespec (struct timespec *suma,
                   const struct timespec *sumando1,
                   const struct timespec *sumando2 );

/* Objeto Regulador que hereda de FDT sus metodos y atributos. Adicionalmente define metodos de obtención de las
 * variables Kp y Referencia (entrada). Define su propia función read con llamada al conversor.
 * Se implementa una espera absoluta de 2ms que simula la conversión
 */

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

    pthread_mutex_lock(&conv->mutex); //Obtenemos mutex para el recurso compartido (el registro de control)

    while(!conv->CSR.conversionAcabada()) {             //Si el conversor esta en uso
        pthread_cond_wait(&conv->cond,&conv->mutex);    //Espera condicionada para no utilizar tiempo de CPU
    }

    //Modificacion de valores en el CSR
    conv->CSR.prepararConversion(chan);
    conv->CSR.lanzarConversion();

    pthread_mutex_unlock(&conv->mutex);

    //Conversión lanzada
    conv->convert(value);

    pthread_mutex_lock(&conv->mutex);

    //Se espera al fin de la conversion
    while(!conv->CSR.conversionAcabada()){
        pthread_cond_wait(&conv->convFinished,&conv->mutex);
    }

    if (conv->CSR.error()){
        pthread_cond_signal(&conv->cond);
        pthread_mutex_unlock(&conv->mutex);
        return -1;
    }

    (*resultado) = (conv->getRegistroDatos());

    clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME,&fin,NULL); //Espera hasta los 2ms

    pthread_cond_signal(&conv->cond);
    pthread_mutex_unlock(&conv->mutex);

    return 0;
}


