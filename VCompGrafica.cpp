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
}

void VCompGrafica::add(double UkValue, double YkValue, double tiempo, double ref1){
    for (int i=m_tam-1;i>0;i--){
        valuesYk[i] = valuesYk[i-1];
        valuesUk[i] = valuesUk[i-1];
    }
    valuesYk[0] = YkValue;
    valuesUk[0] = UkValue;
    emit sendValue(tiempo,ref1,YkValue);
}

double* VCompGrafica::getTablaUk(){
    return valuesUk;
}

double* VCompGrafica::getTablaYk(){
    return valuesYk;
}

VCompGrafica::~VCompGrafica(){
    delete valuesYk;
    delete valuesUk;
}

