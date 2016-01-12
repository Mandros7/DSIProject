#include "Planta.h"

//Clase que hereda de FDT todos los metodos y atributos. En este caso solo se requiere definir una función read
double Planta::read() {
    return m_entrada->getValor(); //Simplemente devuelve el valor alojado en la variable de entrada
}

Planta::Planta(VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam) :
    FDT(entrada,salida,coefNum,coefDen,tam){
    // Nada que asignar, se realiza en la llamada al constructor de FDT
}
