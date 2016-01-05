#ifndef PLANTA_H
#define PLANTA_H

#include "FDT.h"
class Planta : FDT {
public:
	double read();

    Planta(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum, double* coefDen, int tam);
};

#endif //PLANTA_H
