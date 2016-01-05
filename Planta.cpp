#include "Planta.h"

double Planta::read() {
    return m_entrada->getValor()[0];
}

Planta::Planta(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum, double* coefDen, int tam) :
    FDT(entrada,salida,salidasTabla,coefNum,coefDen,tam){
    // Nada que asignar
}
