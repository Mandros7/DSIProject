#include "VCompGrafica.h"

VCompGrafica::VCompGrafica(QObject *parent,int tam) : QObject(parent)
{
    m_tam = tam;
    valuesYk = new double[tam];
    valuesUk = new double[tam];
    for (int i=0;i<tam;i++){
        valuesYk[i]=0;
        valuesUk[i]=0;
    }

    pthread_mutexattr_t atributos;
    pthread_mutexattr_init(&atributos);
    pthread_mutexattr_setprotocol(&atributos,PTHREAD_PRIO_PROTECT);
    pthread_mutex_init(&mutex,&atributos);
}

void VCompGrafica::add(double UkValue, double YkValue, double tiempo, double ref1){
    pthread_mutex_lock(&mutex);
    for (int i=m_tam-1;i>0;i--){
        valuesYk[i] = valuesYk[i-1];
        valuesUk[i] = valuesUk[i-1];
    }
    valuesYk[0] = YkValue;
    valuesUk[0] = UkValue;
    pthread_mutex_unlock(&mutex);
    emit sendValue(tiempo,ref1,YkValue); //Se lanza la signal para el objeto tipo Graf.
}

double* VCompGrafica::getTablaUk(){
    pthread_mutex_lock(&mutex);
    double *values = valuesUk;
    pthread_mutex_unlock(&mutex);
    return values;
}

double* VCompGrafica::getTablaYk(){
    pthread_mutex_lock(&mutex);
    double *values = valuesYk;
    pthread_mutex_unlock(&mutex);
    return values;
}

VCompGrafica::~VCompGrafica(){
    delete valuesYk;
    delete valuesUk;
}

