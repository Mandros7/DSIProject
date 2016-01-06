#include "Planta.h"

double Planta::read() {
    return m_entrada->getValor();
}

Planta::Planta(VComp* kp, VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam) :
    FDT(kp,entrada,salida,coefNum,coefDen,tam){
    // Nada que asignar
}
