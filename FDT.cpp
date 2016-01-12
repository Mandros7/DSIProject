#include "FDT.h"

// Asignacion de parametros a variables internas de la clase
FDT::FDT(VComp* entrada, VComp* salida, double* coefNum, double* coefDen, int tam) {
    m_entrada = entrada;
    m_salida = salida;
    m_coefNum = coefNum;
    m_coefDen = coefDen;
    m_tam = tam;

    // Inicializacion de tablas internas de entradas/salidas
    m_yk = new double[tam];
    m_xk = new double[tam];
    for (int i=0;i<tam;i++){
        m_yk[i] = 0;
        m_xk[i] = 0;
    }
}

// Simulacion de funcionamiento del bloque
double FDT::simular(double n_entrada) {
    desplazarTabla(m_xk,n_entrada);
    desplazarTabla(m_yk,0);
    m_yk[0] = (productoEscalar(m_xk,m_coefNum) - productoEscalar(m_yk,m_coefDen));
    m_salida->setValor(m_yk[0]); //Se escribe el nuevo valor en variable compartida
    return m_yk[0];              //Se retorna para su posible uso en el main
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
