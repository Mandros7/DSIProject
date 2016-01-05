#include "gui.h"
#include <QApplication>
#include "Conversor.h"
#include "Sensor.h"
#include "Planta.h"
#include "Regulador.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void * planta (void * param){
    FDT* planta = (FDT *)param;
    while(1){
        double entrada = planta->read();
        double salida = planta->simular(entrada);
        cout << "Planta|\tEntrada: "<<entrada<<".\tSalida: " <<salida<< endl;
        usleep(100000);
    }

    return 0;
}

void * regulador (void * param){
    FDT* regulador = (FDT *)param;
    while(1){
        double entrada = regulador->read();
        double salida = regulador->simular(entrada);
        //cout << "Regulador|\tEntrada: "<<entrada<<".\tSalida: " <<salida<< endl;
        usleep(100000);
    }
    return 0;
}

int main(int argc, char *argv[])
{

    double num[] = {0,
                    0.002059,
                    0.001686
                   };

    double den[] = {1,
                    -1.511,
                    0.5488};

    double pid_num[] = {414.1,
                        -647.8,
                        250.1,
                        0};

    double pid_den[] = {1,
                        0.82,
                        -1,
                       -0.82};
    int tam = 5;
    double *ykTablaValor = new double[tam];
    double *ukTablaValor = new double[tam];
    double *ukValor = new double[1];
    ukValor[0] = 0;
    double *ykValor = new double[1];
    ykValor[0] = 0;
    double *refValor = new double[1];
    refValor[0] = 10;
    VComp uk = VComp(ukValor,1);
    VComp yk = VComp(ykValor,1);
    VComp ref = VComp(refValor,1);
    VComp ykTabla = VComp(ykTablaValor,tam);
    VComp ukTabla = VComp(ukTablaValor,tam);


    Conversor c = Conversor();
    Sensor s = Sensor(&yk);

    Planta *p = new Planta(&uk,&yk,&ykTabla,num,den,3);
    Regulador *r = new Regulador(&ref,&uk,&ukTabla,pid_num,pid_den,4,&c,&s,1);

    pthread_t pla, reg;		/* threads que se van a crear */

    pthread_create(&pla, NULL, planta, (void*)p);
    pthread_create(&reg, NULL, regulador, (void*)r);

    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
