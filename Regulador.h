#ifndef REGULADOR_H
#define REGULADOR_H

#include "FDT.h"
#include "Sensor.h"
#include "Conversor.h"

class Regulador : public FDT {

private:
    Sensor *sens;
    Conversor *conv;
    int chan;

public:
    Regulador(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum,
              double* coefDen, int tam, Conversor* c, Sensor *s, int channel);

	double read();
};

#endif //REGULADOR_H
