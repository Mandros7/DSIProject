#include "FDT.h"

FDT::FDT(VComp* kp,VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam) {
    m_entrada = entrada;
    m_salida = salida;
    m_kp = kp;
    m_coefNum = coefNum;
    m_coefDen = coefDen;
    m_tam = tam;

    m_yk = new double[tam];
    m_xk = new double[tam];
    for (int i=0;i<tam;i++){
        m_yk[i] = 0;
        m_xk[i] = 0;
    }
}

double* FDT::aplicarGanancia(double valor,double* v){
    double * vec = new double[m_tam];
    for (int i=0;i<m_tam;i++){
        vec[i] = v[i]*valor;
    }
    return vec;
}

double FDT::simular(double n_entrada) {
    desplazarTabla(m_xk,n_entrada);
    desplazarTabla(m_yk,0);
    m_yk[0] = productoEscalar(m_xk,aplicarGanancia(m_kp->getValor(),m_coefNum)) - productoEscalar(m_yk,m_coefDen);
    m_salida->setValor(m_yk[0]);
    return m_yk[0];
}

double FDT::productoEscalar(double* vector1, double* vector2) {
    double resultado = 0;
    for (int i = 0;i<m_tam;i++){
        resultado = resultado + vector1[i]*vector2[i];
    }
    return resultado;
}

void FDT::desplazarTabla(double* tabla, double n_valor) {
    for (int i=m_tam-1;i>0;i--){
        tabla[i] = tabla[i-1];
    }
    tabla[0] = n_valor;
}
