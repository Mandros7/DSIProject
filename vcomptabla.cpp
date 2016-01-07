#include "vcomptabla.h"

VCompTabla::VCompTabla(QObject *parent,int tam) : QObject(parent)
{
    m_tam = tam;
    values = new double[tam];
    for (int i=0;i<tam;i++){
        values[i]=0;
    }
}

void VCompTabla::add(double n_value, double tiempo, double ref1){
    for (int i=m_tam-1;i>0;i--){
        values[i] = values[i-1];
    }
    values[0] = n_value;
    emit sendValue(tiempo,ref1,n_value);
}

double* VCompTabla::getTabla(){
    return values;
}

VCompTabla::~VCompTabla(){
    delete values;
}

