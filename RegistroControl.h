#ifndef RegistroControl_H
#define RegistroControl_H

typedef unsigned char uint8;
typedef struct{
    uint8    Start:1,
                     :1,
                Canal:2,
                Done:1,
                IE:1,
                Error:2;
            }CSR_Campos;


class RegistroControl
{
private:
    CSR_Campos registro;

public:
    RegistroControl();
    void prepararConversion(int Canal);
    void acabarConversion();
    void lanzarConversion();
    bool conversionAcabada();
    bool error();
};

#endif // CSR_H
