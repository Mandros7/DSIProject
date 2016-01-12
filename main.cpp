#include "gui.h"
#include <QApplication>
#include "Conversor.h"
#include "Sensor.h"
#include "Planta.h"
#include "Regulador.h"
#include "VComp.h"
#include "VCompGrafica.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <graf.h>
#include "ui_gui.h"
#include <sched.h>

// Variables globales compartidas por hilos workers y de interfaz
// Variables VComp contienen un double inicializado con el valor del parametro
// Variables VCompGrafica contiene un array de double inicializado entero a 0. (segundo parametro es el tamaño)
VComp kp0(1);
VComp kp1(0.1);
VComp uk1(0);
VComp yk1(0);
VComp ref1(5);
VCompGrafica TablaSalidas1(0,5);
VComp kp2(5);
VComp uk2(0);
VComp yk2(0);
VComp ref2(5);
VCompGrafica TablaSalidas2(0,5);
bool running;

// Estructura de datos que se pasa a los hilos
// En el caso de los hilos tipo planta, no todos los atributos se asignan
struct datosSistema{
    VCompGrafica* tablaSalida;
    struct timespec periodo;   // Periodo de ejecucion
    FDT * fdt;                 // Objeto tipo FDT, que puede ser cualquiera de los hijos: planta, regulador
    int numLazo;               // Identificador de lazo de control
};

// Método de adición de estructuras de tiempo. Comprueba el desborde de tv_nsec para aumentar en consecuenci
// la variable tv_sec
void add_timespec (struct timespec *suma,
                   const struct timespec *sumando1,
                   const struct timespec *sumando2 )
{
    suma->tv_sec = sumando1->tv_sec  + sumando2->tv_sec;
    suma->tv_nsec = sumando1->tv_nsec + sumando2->tv_nsec;
    if (suma->tv_nsec >= 1E9)
    {
        suma->tv_sec ++;
        suma->tv_nsec -= 1E9;
    }
}

// Metodo que transforma estructuras de tipo timespec a double y las resta.
double get_TimeStamp (struct timespec inicio, struct timespec ahora){
    return (double)(ahora.tv_sec+ahora.tv_nsec*(1E-9)) - (double)(inicio.tv_sec+inicio.tv_nsec*(1E-9));
}

// Codigo del hilo de planta. Lee los datos, simula comportamiento utilizando esperas absolutas (TIMER_ABSTIME)
void * planta (void * param){
    datosSistema* datos = (datosSistema *)param;
    Planta * p = (Planta*) datos->fdt;
    struct timespec inicial,periodo,siguiente_activacion;
    periodo = datos->periodo;
    clock_gettime(CLOCK_REALTIME, &siguiente_activacion);
    inicial = siguiente_activacion;
    while(running){
        double resultado = p->read();
        p->simular(resultado);
        add_timespec(&siguiente_activacion, &siguiente_activacion, &periodo);
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME,&siguiente_activacion, NULL);
    }
    return 0;
}

/* Codigo del hilo del regulador, similar al de planta, adicionalmente comprueba el resultado de la conversion
 * implicita en la función read y añade los datos a la tabla compartida con la interfaz, actuando como lanzador
 * del plot en el objeto tipo Graf.
*/
void * regulador (void * param){
    datosSistema* datos = (datosSistema *)param;
    Regulador * p = (Regulador*) datos->fdt;
    struct timespec inicial,periodo,siguiente_activacion;
    periodo = datos->periodo;
    clock_gettime(CLOCK_REALTIME, &siguiente_activacion);
    inicial = siguiente_activacion;
    while(running){
        double resultado;
        int entrada = p->read(&resultado,datos->numLazo);
        if (entrada!=-1){
            double salida = p->simular((p->getRef()->getValor()-resultado)*p->getKp()->getValor());
            datos->tablaSalida->add(salida,resultado,get_TimeStamp(inicial,siguiente_activacion),p->getRef()->getValor());
        }
        add_timespec(&siguiente_activacion, &siguiente_activacion, &periodo);
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME,&siguiente_activacion, NULL);
    }
    return 0;
}

int main(int argc, char *argv[])
{

    // Declaracion de arrays de double que contienen numeradores y denominadores de funciones de transferencia
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
                        -0.1998*2445.4};

    double pid_den2[] = {
                         1,
                       -0.9998};



    // Declaracion de objetos que participan en los lazos de control
    Conversor c = Conversor();
    Sensor s1 = Sensor(&yk1);
    Sensor s2 = Sensor(&yk2);

    Planta *p1 = new Planta(&uk1,&yk1,num1,den1,3);
    Regulador *r1 = new Regulador(&kp1,&ref1,&uk1,pid_num1,pid_den1,4,&c,&s1);
    Planta *p2 = new Planta(&uk2,&yk2,num2,den2,2);
    Regulador *r2 = new Regulador(&kp2,&ref2,&uk2,pid_num2,pid_den2,2,&c,&s2);

    // Declaracion e inicializacion de las estructuras de datos para los hilos
    struct datosSistema planta1,regulador1,planta2,regulador2;
    planta1.fdt = p1;
    planta1.periodo.tv_sec=0;
    planta1.periodo.tv_nsec=50000000/2;
    regulador1.fdt = r1;
    regulador1.tablaSalida = &TablaSalidas1;
    regulador1.periodo.tv_sec=0;
    regulador1.periodo.tv_nsec=50000000;
    regulador1.numLazo = 0;
    planta2.fdt = p2;
    planta2.periodo.tv_sec=0;
    planta2.periodo.tv_nsec=20000000/2;
    regulador2.fdt = r2;
    regulador2.tablaSalida = &TablaSalidas2;
    regulador2.periodo.tv_sec=0;
    regulador2.periodo.tv_nsec=20000000;
    regulador2.numLazo = 1;


    running = true; // Se inicializa la variable global para los hilos previamente


    pthread_t pla1, reg1, pla2, reg2;		// Threads que se van a crear

    // PLANIFICACION Y PRIORIDADES
    // Sistema tipo FIFO con prioridades relativas entre los hilos.
    // Se asignan en funcion de su periodo absoluto de ejecucion.
    sched_param param_P1, param_R1, param_P2, param_R2;
    pthread_attr_t propPla1,propPla2,propReg1,propReg2;

    param_R1.__sched_priority = 1;
    param_P1.__sched_priority = 2;
    param_R2.__sched_priority = 3;
    param_P2.__sched_priority = 4;

    pthread_attr_init(&propPla1);
    pthread_attr_setschedparam(&propPla1,&param_P1);
    pthread_attr_setschedpolicy(&propPla1,SCHED_FIFO);
    pthread_attr_setinheritsched(&propPla1,PTHREAD_PRIO_PROTECT);


    pthread_attr_init(&propPla2);
    pthread_attr_setschedparam(&propPla2,&param_P2);
    pthread_attr_setschedpolicy(&propPla2,SCHED_FIFO);
    pthread_attr_setinheritsched(&propPla2,PTHREAD_PRIO_PROTECT);

    pthread_attr_init(&propReg1);
    pthread_attr_setschedparam(&propReg1,&param_R1);
    pthread_attr_setschedpolicy(&propReg1,SCHED_FIFO);
    pthread_attr_setinheritsched(&propReg1,PTHREAD_PRIO_PROTECT);


    pthread_attr_init(&propReg2);
    pthread_attr_setschedparam(&propReg2,&param_R2);
    pthread_attr_setschedpolicy(&propReg2,SCHED_FIFO);
    pthread_attr_setinheritsched(&propReg2,PTHREAD_PRIO_PROTECT);

    // Se lanzan los hilos
    pthread_create(&pla1, &propPla1, planta, (void*)&planta1);
    pthread_create(&reg1, &propReg1, regulador, (void*)&regulador1);
    pthread_create(&pla2, &propPla2, planta, (void*)&planta2);
    pthread_create(&reg2, &propReg2, regulador, (void*)&regulador2);

    QApplication a(argc, argv);
    GUI w;

    // Se crean los objetos que gestionan las graficas de la interfaz
    // Es necesario que el objeto GUI tenga accesible el atributo UI.
    Graf g1(0.001,w.ui->customPlot);
    Graf g2(0.001,w.ui->customPlot2);

    // Conexion de las signals lanzadas por los objetos que contienen datos compartidos con interfaz
    // y slots de los objetos GRAF.
    QObject::connect(&TablaSalidas1,SIGNAL(sendValue(double,double,double)),&g1,SLOT(dataSlot(double,double,double)));
    QObject::connect(&TablaSalidas2,SIGNAL(sendValue(double,double,double)),&g2,SLOT(dataSlot(double,double,double)));
    w.show();

    return a.exec();
}
