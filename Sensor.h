#ifndef SENSOR_H
#define SENSOR_H

#include "VComp.h"
class Sensor {

private:
    VComp* m_entrada;

public:
    Sensor(VComp* entrada);

    short getValue();
};

#endif // SENSOR_H
