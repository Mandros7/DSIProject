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
    struct timespec periodo;

public:
    Regulador(VComp* kp,VComp* entrada, VComp* salida, double* coefNum,
              double* coefDen, int tam, Conversor* c, Sensor *s, int channel);

    int read(double * resultado);
    VComp* getRef();
};

#endif //REGULADOR_H
