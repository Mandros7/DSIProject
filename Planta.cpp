#include "Planta.h"

int Planta::read(double *resultado) {
    (*resultado) = m_entrada->getValor();
    return 0;
}

Planta::Planta(VComp* kp, VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam) :
    FDT(kp,entrada,salida,coefNum,coefDen,tam){
    // Nada que asignar
}
