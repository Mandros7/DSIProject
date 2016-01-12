#include "RegistroControl.h"


/* Objeto de registro de control del conversor en el que se implementan los metodos de manipulación de la estructura
 * CSR_Campos definida en la cabecera, mediante operaciones de bajo nivel.
 */
RegistroControl::RegistroControl()
{
    registro.Done |= 1; //Ponemos Done a 1 inicialmente
    registro.Error &= 0;//Ponemos Error a 0 inicialmente
}

void RegistroControl::prepararConversion(int Canal){
    registro.IE |= 1; //Ponemos IE a 1
    switch (Canal){
        case 0:
             registro.Canal &=0;
            break;
        case 1:
        registro.Canal &=0; //Primero lo ponemos todo a cero (Por si habia combinaciones distintas)
        registro.Canal |=1; //Luego ponemos a 1
            break;
        default:
            break;
    }
}

void RegistroControl::lanzarConversion(){
    registro.Start |=1; //Ponemos a 1 START
}

void RegistroControl::acabarConversion(){
    registro.Start &=0; //Ponemos a 0 START
    registro.Done |=1;  //Ponemos a 1 DONE
}

bool RegistroControl::conversionAcabada(){
    return registro.Done;
}

bool RegistroControl::error(){
    return registro.Error;
}

