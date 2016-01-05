#include "Sensor.h"

Sensor::Sensor(VComp* entrada) {
    m_entrada = entrada;
}

short Sensor::getValue() {
    double valor = m_entrada->getValor()[0];
    if (valor>20)
        valor = 20;
    if (valor<0)
        valor = 0;
    return (short)(valor/1000.0*500.0*4095.0/10.0);
}
