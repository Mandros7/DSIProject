#include "RegistroControl.h"

RegistroControl::RegistroControl()
{
    registro.Done |= 1;
    registro.Error &= 0;
}

void RegistroControl::prepararConversion(int Canal){
    registro.IE |= 1; //Ponemos IE a 1
    switch (Canal){
        case 0:
             registro.Canal &=0;
            break;
        case 1:
        registro.Canal &=0; //Primero lo ponemos todo a cero (Por si habia alguna combinacion)
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
    registro.Start &=0;
    registro.Done |=1;
}

bool RegistroControl::conversionAcabada(){
    return registro.Done;
}

bool RegistroControl::error(){
    return registro.Error;
}

