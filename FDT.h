#ifndef FDT_H
#define FDT_H

#include "VComp.h"
class FDT {

private:
    double* m_xk;
    double* m_yk;
    int m_tam;
    double* m_coefNum;
    double* m_coefDen;

protected:
    VComp* m_entrada;
    VComp* m_salida;
    VComp* m_salidasTabla;

public:
	virtual double read() = 0;

    FDT(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum, double* coefDen, int tam);

	double simular(double n_entrada);

private:
	double productoEscalar(double* vector1, double* vector2);

	void desplazarTabla(double* tabla, double n_valor);
};

#endif //FDT_H
