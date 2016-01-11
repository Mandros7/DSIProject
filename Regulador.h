#ifndef REGULADOR_H
#define REGULADOR_H

#include "FDT.h"
#include "Sensor.h"
#include "Conversor.h"

class Regulador : public FDT {

private:
    Sensor *sens;
    Conversor *conv;
    struct timespec periodo;
    VComp* m_kp;

public:
    Regulador(VComp* kp,VComp* entrada, VComp* salida, double* coefNum,
              double* coefDen, int tam, Conversor* c, Sensor *s);

    int read(double * resultado, int chan);
    VComp* getRef();
    VComp* getKp();
};

#endif //REGULADOR_H
