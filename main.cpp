#include "gui.h"
#include <QApplication>
#include "Conversor.h"
#include "Sensor.h"
#include "Planta.h"
#include "Regulador.h"
#include "VComp.h"
#include "vcomptabla.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

VComp kp0(1);
VComp kp1(1);
VComp uk1(0);
VComp yk1(0);
VComp ref1(1);
VCompTabla yk1TablaSalidas(100);
VCompTabla uk1TablaSalidas(100);
VComp kp2(1);
VComp uk2(0);
VComp yk2(0);
VComp ref2(1);
VCompTabla yk2TablaSalidas(100);
VCompTabla uk2TablaSalidas(100);

struct datosSistema{
    VCompTabla* tablaSalida;
    struct timespec periodo;
    FDT * fdt;
};

void add_timespec (struct timespec *suma,
                   const struct timespec *sumando1,
                   const struct timespec *sumando2 )
{
    suma->tv_sec = sumando1->tv_sec  + sumando2->tv_sec;  // calcula segundos
    suma->tv_nsec = sumando1->tv_nsec + sumando2->tv_nsec; // calcula nsegundos
    if (suma->tv_nsec >= 1E9)  // ver si tenemos un segundo completo
    {
        suma->tv_sec ++;		// añadir 1 a la cuenta de segundos
        suma->tv_nsec -= 1E9;	// calcular los ns que quedan
    }
}

void * sistema (void * param){
    datosSistema* datos = (datosSistema *)param;
    FDT * p = (FDT*) datos->fdt;
    struct timespec periodo,siguiente_activacion;
    periodo = datos->periodo;
    clock_gettime(CLOCK_REALTIME, &siguiente_activacion);
    while(1){
        double entrada = p->read();
        double salida = p->simular(entrada);
        datos->tablaSalida->add(salida);

        add_timespec(&siguiente_activacion, &siguiente_activacion, &periodo);
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME,&siguiente_activacion, NULL);
    }

    return 0;
}

int main(int argc, char *argv[])
{

    double num1[] = {0,
                    0.002059,
                    0.001686
                   };

    double den1[] = {1,
                    -1.511,
                    0.5488};

    double pid_num1[] = {414.1,
                        -647.8,
                        250.1,
                        0};

    double pid_den1[] = {1,
                        0.82,
                        -1,
                       -0.82};

    double num2[] = {0,
                    1.999E-5
                   };

    double den2[] = {1,
                    -0.999};

    double pid_num2[] = {0.2*2445.4,
                        -1.998*2445.4,
                        0};

    double pid_den2[] = {0,
                        1,
                       -0.9998};



    Conversor c = Conversor();
    Sensor s1 = Sensor(&yk1);
    Sensor s2 = Sensor(&yk2);

    Planta *p1 = new Planta(&kp0,&uk1,&yk1,num1,den1,3);
    Regulador *r1 = new Regulador(&kp1,&ref1,&uk1,pid_num1,pid_den1,4,&c,&s1,1);
    Planta *p2 = new Planta(&kp0,&uk2,&yk2,num2,den2,2);
    Regulador *r2 = new Regulador(&kp2,&ref2,&uk2,pid_num2,pid_den2,3,&c,&s2,2);

    struct datosSistema planta1,regulador1,planta2,regulador2;
    planta1.fdt = p1;
    planta1.tablaSalida = &yk1TablaSalidas;
    planta1.periodo.tv_sec=0;
    planta1.periodo.tv_nsec=300000000;
    regulador1.fdt = r1;
    regulador1.tablaSalida = &uk1TablaSalidas;
    regulador1.periodo.tv_sec=0;
    regulador1.periodo.tv_nsec=300000000;
    planta2.fdt = p2;
    planta2.tablaSalida = &yk2TablaSalidas;
    planta2.periodo.tv_sec=0;
    planta2.periodo.tv_nsec=300000000;
    regulador2.fdt = r2;
    regulador2.tablaSalida = &uk2TablaSalidas;
    regulador2.periodo.tv_sec=0;
    regulador2.periodo.tv_nsec=300000000;

    pthread_t pla1, reg1, pla2, reg2;		/* threads que se van a crear */

    pthread_create(&pla1, NULL, sistema, (void*)&planta1);
    pthread_create(&reg1, NULL, sistema, (void*)&regulador1);
    pthread_create(&pla2, NULL, sistema, (void*)&planta2);
    pthread_create(&reg2, NULL, sistema, (void*)&regulador2);


    //pthread_create(&pla2, NULL, planta, (void*)p2);
    //pthread_create(&reg2, NULL, regulador, (void*)r2);

    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
