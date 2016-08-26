/*
 * Programa que simula el proceso en una cola de bancos
 * @author: %% estudiante Ing. Civil Informatica UCM.
 * @version: version 1.0
 */

/* Bloque de identificacion de Sistema Operativo : 
* Se usa para setear variables usadas de forma diferente en Linux y Windows
*/
#ifdef __unix__  
    #define OS_Windows 0
	#define OS_Clear "clear"
#elif defined(_WIN32) || defined(WIN32)
	#define OS_Windows 1
	#define OS_Clear "cls"
#endif
/* End ...................................................... */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Declaracion de struct */
typedef struct cliente
{
	int tipo_cuenta;
	int tipo_servicio;
	int tiempoMax;
    int tiempoEspera;
	struct cliente *siguiente;
}s_cl;

typedef struct cola_Banco
{
	s_cl *FRENTE;
	s_cl *FINAL;
	int tam;// tamaño de la lista
}s_cola;



/* Declaracion de funciones */
void mostrarOpciones();
s_cl *crearCliente(); // Crea un nuevo cliente para ingresarlo a una cola
s_cola *crearCola(); // Crea una cola vacia y retorna un puntero
void encolar(s_cola *, s_cl *); // encola el cliente
s_cl *desencolar(s_cola *); // encola el cliente
int isEmpty(s_cola *);
s_cola *ingresarClientes(int n); // simulacion del ingreso de N clientes
void Simulacion(s_cola *);  // trabajara con las colas globales
void calcularEstadisticas(int n);
/* FIN - Declaracion de funciones */



/*  variables globales y constantes */
const int SALIR = 1;	// Variable de control de ejecucion
s_cola *colaAtendidos,*colaAbandonos; 
const int tiempo_servicios[]  = {180, 240, 480, 300, 120};



/* Main del programa - Funcion principal */
int main()
{	
	/* Inicializacion */
	srand (time());
	int n=0, cont=0;
	s_cola *filaBanco;

    do {
        mostrarOpciones();
        scanf("%d", &n);
     	filaBanco = crearCola();
		filaBanco = ingresarClientes(n);
		Simulacion(filaBanco);
		printf("Cola de atendidos: %d clientes\n", colaAtendidos->tam );
		printf("Cola de abandonos: %d clientes\n", colaAbandonos->tam );
		//printf("Numero random: %d\n", rand()%9+1 );
		//system("pause");
         cont++;
    } while (cont < SALIR);

	return 0;
}
/* End of main() */


/* Implementacion de las funciones */
void mostrarOpciones()
{
	system(OS_Clear);
	fflush(stdin);
	puts("Ingresa la cantidad de clientes: ");
}

s_cl *crearCliente()
{
	int tcuenta = rand()%4 + 1;
	int tservicio = rand()%5 + 1;
	int tMax = rand()%3600+1;
    int tEspera = 0;

	s_cl *nodo = (s_cl *)malloc(sizeof(s_cl));
	nodo->siguiente = NULL;
	nodo->tipo_cuenta = tcuenta;
	nodo->tipo_servicio = tservicio;
	nodo->tiempoMax = tMax;
	nodo->tiempoEspera = tEspera;

	return nodo; 
}

/* Crea una lista de Agendas vacia y le asigna memoria */
s_cola *crearCola()
{
	s_cola *colaNueva = (s_cola *)malloc(sizeof(s_cola));
	colaNueva->FRENTE = NULL;
	colaNueva->FINAL = NULL;
	colaNueva->tam = 0;

	return colaNueva;
}

/* inserta un elemento Agenda en una lista de Agendas */
void encolar(s_cola *filabanco, s_cl *nuevocliente)
{
	if(filabanco!=NULL && nuevocliente!=NULL)
	{
		if (isEmpty(filabanco)==0)
		{
			filabanco->FRENTE = nuevocliente;
			filabanco->FINAL = nuevocliente;
		}else{
			nuevocliente->siguiente = filabanco->FINAL;
			filabanco->FINAL = nuevocliente;
		}
		filabanco->tam += 1; // cada vez que se inserta se incrementa el contador de elementos de la lista.
	}else
		printf("ERROR: No se puede insertar el elemento en la cola.\n");
}

/* inserta un elemento NODO en una lista_simple de una Agenda */
s_cl *desencolar(s_cola *filabanco)
{
	s_cl *Aux;

	if (isEmpty(filabanco) > 0 && filabanco->FINAL!=NULL && filabanco->FRENTE!=NULL)
	{
		Aux = filabanco->FINAL;
		if(filabanco->FRENTE == filabanco->FINAL){
			filabanco->FRENTE = NULL;
			filabanco->FINAL = NULL;
			filabanco->tam -= 1;
			return Aux;
		}

		do{
			if(Aux->siguiente == filabanco->FRENTE){
				filabanco->FRENTE = Aux;
				filabanco->tam -= 1;
			}
			else{
				Aux = Aux->siguiente;
			}
		}while( Aux != filabanco->FRENTE );

	}else
		puts("\nERROR: No se puede desencolar ya que la fila de banco esta vacia.");

	return Aux->siguiente;
}

/* Verifica si la lista esta vacia */
int isEmpty(s_cola *filabanco)
{
	int cont = 0;
	if (filabanco->FRENTE!=NULL)
	{
		s_cl *Aux = filabanco->FINAL;
		while(Aux!=NULL){
			Aux = Aux->siguiente;
			cont++;
		}
	}
	return cont;
}

s_cola *ingresarClientes(int n)
{
	int i=0;
	s_cola *colabanco = crearCola();

	for (i = 0; i < n; i++) {
		s_cl *cl = crearCliente();
		encolar(colabanco, cl);
	}

	return colabanco;
}

void Simulacion(s_cola *filabanco)
{
    double demora = 0, max=0;
    colaAtendidos = crearCola();
    colaAbandonos = crearCola();

    while(isEmpty(filabanco)){
        demora += tiempo_servicios[filabanco->FRENTE->tipo_servicio];
        printf("demora acumulada: %f\n", demora);
        max = filabanco->FRENTE->tiempoMax;
        s_cl *cl = desencolar(filabanco);
        cl->tiempoEspera = demora;
        if(demora <= max){
            encolar(colaAtendidos,cl); 
        }else{
            encolar(colaAbandonos,cl);
        }
    }
}