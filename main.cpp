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
        usleep(1000000);
    }

    return 0;
}

void * regulador (void * param){
    FDT* regulador = (FDT *)param;
    while(1){
        double entrada = regulador->read();
        double salida = regulador->simular(entrada);
        cout << "Regulador|\tEntrada: "<<entrada<<".\tSalida: " <<salida<< endl;
        usleep(1000000);
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
    //int tam = 5;
    //double *ykTablaValor = new double[tam];
    //double *ukTablaValor = new double[tam];

    VComp kp0 = VComp(1);
    VComp kp1 = VComp(1);
    //VComp kp2 = VComp(1);
    VComp uk = VComp(0);
    VComp yk = VComp(0);
    VComp ref = VComp(1);
    //VComp ykTabla = VComp(ykTablaValor,tam);
    //VComp ukTabla = VComp(ukTablaValor,tam);


    Conversor c = Conversor();
    Sensor s = Sensor(&yk);

    Planta *p1 = new Planta(&kp0,&uk,&yk,num,den,3);
    Regulador *r1 = new Regulador(&kp1,&ref,&uk,pid_num,pid_den,4,&c,&s,1);
    //Planta *p2 = new Planta(&kp0,&uk,&yk,&ykTabla,num,den,3);
    //Regulador *r2 = new Regulador(&kp2,&ref,&uk,&ukTabla,pid_num,pid_den,4,&c,&s,2);


    pthread_t pla1, reg1; //pla2, reg2;		/* threads que se van a crear */

    pthread_create(&pla1, NULL, planta, (void*)p1);
    pthread_create(&reg1, NULL, regulador, (void*)r1);

    //pthread_create(&pla2, NULL, planta, (void*)p2);
    //pthread_create(&reg2, NULL, regulador, (void*)r2);

    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
