#ifndef PLANTA_H
#define PLANTA_H

#include "FDT.h"
class Planta : public FDT {
public:
    int read(double *resultado);

    Planta(VComp* kp,VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam);
};

#endif //PLANTA_H
