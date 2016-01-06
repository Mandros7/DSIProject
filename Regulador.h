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
    Regulador(VComp* kp,VComp* entrada, VComp* salida, double* coefNum,
              double* coefDen, int tam, Conversor* c, Sensor *s, int channel);

	double read();
};

#endif //REGULADOR_H
