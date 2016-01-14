#include "Sensor.h"

//Clase de sensor que devuelve el valor de la salida de la planta en forma de entero con signo
Sensor::Sensor(VComp* entrada) {
    m_entrada = entrada;
}

//Se acota los valores en función de la saturacion del sensor. En este caso, lee entre 0 y 10V.
short Sensor::getValue() {
    double valor = m_entrada->getValor();
    if (valor>20)
        valor = 20;
    if (valor<-20)
        valor = 20;
    return (short)(valor/1000.0*500.0*4095.0/20.0);
}
