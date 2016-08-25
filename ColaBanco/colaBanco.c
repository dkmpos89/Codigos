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
	S_CL *FRENTE;
	S_CL *FINAL;
	int tam;// tamaño de la lista
}s_cola;

/*
typedef struct AgendaMedica
{
   time_t fechaInicio;
   char *str_fecha_I;
   time_t fechaFin;
   char *str_fecha_F;
   char *especialidad;
   LTASIM  *lista_simple;
   struct AgendaMedica *siguiente;
}AGM;

typedef struct ListadoAgendasMedicas
{
	AGM *INICIO;
	AGM *FIN;
	int tam;// tamaño de la lista
}LTAGM;
*/

/* Declaracion de funciones */
void mostrarOpciones();
s_cl *crearCliente(); // Crea un nuevo cliente para ingresarlo a una cola
s_cola *crearCola(); // Crea una cola vacia y retorna un puntero
void encolar(s_cola *, s_cl *); // encola el cliente
s_cl *desencolar(s_cola *); // encola el cliente
int isEmpty(s_cola *);
s_cola *ingresarClientes(int n); // simulacion del ingreso de N clientes
void Simulacion(s_cola *);  // trabajara con las colas globales
calcularEstadisticas(n);


/* FIN - Declaracion de funciones */



/*  variables globales y constantes */
const int SALIR = 1;	// Variable de control de ejecucion
s_cola *colaAtendidos,colaAbandonos; 

/* Main del programa - Funcion principal */
int main()
{	
	/* Inicializacion */
	s_cola *filaBanco = crearCola();
	int n=0, cont=0;

     do {
         mostrarOpciones();
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
	s_cl *nodo = (s_cl *)malloc(sizeof(s_cl));
	nodo->siguiente = NULL;
	return nodo; 
}

void setFecha(struct tm *tlocal, time_t *tiempo, char fecha[])
{
	char *str = (char *)malloc(20*sizeof(char));
	strcpy(str,fecha);

	tlocal = localtime(tiempo);
	tlocal->tm_sec = tlocal->tm_min = tlocal->tm_hour = 0;

	int numbday = atoi(strtok(str, s));
	int numbmonth = atoi(strtok(NULL, s))-1;
	int numbyear = atoi(strtok(NULL, s));

	if(numbyear <= 1900)
	{
		printf("INFO: La fecha no debe ser menor que: 01-01-1900.\n");
		numbday = 01; numbmonth = 01; numbyear = 1900;
	}
	tlocal->tm_year = numbyear - 1900;
	tlocal->tm_mday = numbday;	
	tlocal->tm_mon = numbmonth;

	*tiempo = mktime(tlocal);	

}

/* Crea una lista de Agendas vacia y le asigna memoria */
LTAGM *crearLista()
{
	LTAGM *nuevaLista = (LTAGM *)malloc(sizeof(LTAGM));
	nuevaLista->INICIO = NULL;
	nuevaLista->FIN = NULL;
	nuevaLista->tam = 0;

	return nuevaLista;
}

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
	int cont = 0;
	if (isEmpty(filabanco) > 0)
	{
		s_cl *Aux = filabanco->FINAL;
		do{
			Aux = Aux->siguiente;
			cont++;
		}(Aux!=filabanco->FRENTE);
	}else
		puts("\nERROR: fila de banco vacia.");

	return Aux;
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



/* inserta un elemento Agenda en una lista de Agendas */
void eliminarAgenda(LTAGM *listaAg)
{
	if(isEmpty(listaAgendas)==0){ puts("INFO: No se puede usar la funcion eliminar en una lista vacia."); getchar(); return;}

	printf("Ingrese el numero de la agenda que se va a eliminar: ");
	char *inp = (char *)malloc(100*sizeof(char));
	scanf("%s", inp);
	int n = atoi(inp);

	AGM *nodo = NULL;
	AGM *agAux = NULL;

	if(listaAg->INICIO!=NULL && n>0 && n<=listaAg->tam)
	{
		/*  Bloque para el caso que se quiera eliminar el primer elemento */
		if (n==1){
			fflush(stdin);
			agAux = listaAg->INICIO;
			if(listaAg->tam==1){
				listaAg->INICIO = NULL;
				listaAg->FIN = NULL;
				free(agAux);
				puts("SUCCESS: Registro Eliminado!\n" );
				puts("Presione cualquier tecla para continuar...");
				getchar();
				return;
			}else{
				listaAg->INICIO = listaAg->INICIO->siguiente;
				free(agAux);
				puts("SUCCESS: Registro Eliminado!\n" );
				puts("Presione cualquier tecla para continuar...");
				getchar();
				return;
			}
		}

		/*  Bloque para el caso que se quiera eliminar un elemento al centro de la lista */
		int i = 0;
		nodo = listaAg->INICIO;
		for (i = 1; i <= listaAg->tam; ++i)
		{
			if(i==n-1){
				agAux = nodo->siguiente;
				nodo->siguiente = agAux->siguiente;
				puts("SUCCESS: Registro Eliminado!\n" );
				break;
			} 
			nodo = nodo->siguiente;
		}
	}else{
		printf("ERROR: No se puede eliminar el elemento %d de la lista.\n", n);
	}
	puts("Presione cualquier tecla para continuar...");
	fflush(stdin);
	getchar();
}



void mostrar_listaAgendas(LTAGM *listaAg)
{
	AGM *auxiliar = malloc(sizeof(AGM)); /* lo usamos para recorrer la lista */
	int i = 0;
	int cont = 1;
	auxiliar = listaAg->INICIO;
	printf("\nMostrando la lista completa:\n\n");
	while (auxiliar!=NULL) 
	{
		printf("ID: %d  -  Especialidad: %s\n", cont,auxiliar->especialidad);
		printf("Fecha de Inicio:  %s\n", auxiliar->str_fecha_I);
		printf("Fecha de Termino: %s\n", auxiliar->str_fecha_F);
		printf("Cantidad de elementos en lista_simple: %d\n\n", auxiliar->lista_simple->tam);
		
		auxiliar = auxiliar->siguiente;
		i++;
		cont++;
	}
	if (i==0) printf( "\nINFO: La lista esta vacia!!\n" );
	free(auxiliar);
	puts("Presione cualquier tecla para continuar...");
	fflush(stdin);
	getchar();
}

void anadir_elementoAg()
{
	AGM *nuevo;
	char *f1 = (char *)malloc(20*sizeof(char));
	char *f2 = (char *)malloc(20*sizeof(char));
	char *esp = (char *)malloc(20*sizeof(char));

	fflush(stdin);
	printf("\nNueva agenda Medica:\n");
	printf("Especialidad:	"); 
	fflush(stdin);
	scanf("%s", esp);
	printf("Fecha de Inicio-->	(dd-mm-yyyy) : "); 
	fflush(stdin);
	scanf("%s", f1);
	printf("Fecha de Termino->	(dd-mm-yyyy) : "); 
	fflush(stdin);
	scanf("%s", f2);
	fflush(stdin);
	if (strlen(f1)==10 && strlen(f2)==10)
	{
		nuevo = crearNuevaAgenda(f1,f2,esp);
		insertarAgenda(listaAgendas, nuevo);
	}else{
		puts("ERROR: Formato de fechas incorrecto!");
		getchar();
	}
	fflush(stdin);
	getchar();
}

void ingresar_elementoLS()
{
	if(isEmpty(listaAgendas)==0){ puts("INFO: Imposible ingresar sub-elementos si no existen agendas creadas."); getchar(); return;}

	AGM * agenda_actual = (AGM *)malloc(sizeof(AGM));
	NLS *nuevo = (NLS *)malloc(sizeof(NLS));
	int numLista, cod_med, turnos_libres, turnos_ocupados;
	char *fecha_atencion = (char *)malloc(20*sizeof(char));

	printf("\nIngrese numero de la Lista en la que se va a insertar: ");
	scanf("%d", &numLista);
	printf("Ingrese el codigo del medico:	"); fflush(stdin);
	scanf("%d", &cod_med);
	printf("Ingrese la fecha de atencion--> (dd-mm-yyyy): "); fflush(stdin);
	scanf("%s", fecha_atencion);
	printf("Ingrese la cantidad de turnos libres: "); fflush(stdin);
	scanf("%d", &turnos_libres);
	printf("Ingrese la cantidad de turnos ocupados: "); fflush(stdin);
	scanf("%d", &turnos_ocupados);

	if (strlen(fecha_atencion)==10)
	{
		nuevo = crearNodoLTASIM(cod_med, fecha_atencion, turnos_libres, turnos_ocupados);
		agenda_actual = obtener_agenda(NULL, numLista);
		if(agenda_actual!=NULL)
			insertarNodo(agenda_actual->lista_simple, nuevo);
		else
			printf("ERROR: No se puede insertar el elemento en la lista %d\n", numLista);
	}else{
		puts("ERROR: Formato de fechas incorrecto!");
	}
	fflush(stdin);
	getchar();
}

int verificar_turno(int num_agenda, int cod_medico, char fecha_atencion[])
{
	AGM * agenda_actual = (AGM *)malloc(sizeof(AGM));
	agenda_actual = obtener_agenda(NULL, num_agenda);

	if(agenda_actual!=NULL){
		NLS * auxiliar;
		auxiliar = agenda_actual->lista_simple->INICIO;
		while (auxiliar!=NULL) 
		{
			if(auxiliar->codigo_medico == cod_medico) {
				if((*(auxiliar->str_fecha) = *fecha_atencion) && (auxiliar->turnos_libres>0))
					return 0; // 0 = Encontrado!
			}
			auxiliar = auxiliar->siguiente;
		}
	}else{
		puts("ERROR: No se encontro la agenda seleccionada!");
		return 1;// 1 = return ERROR
	}
	return -1; // -1 = No encontrado
}

AGM *obtener_agenda(LTAGM *lA, int numLista)
{
	LTAGM * listaAg;
	AGM * auxiliar;
	int i = 1;

	if (lA!=NULL) listaAg = lA;
	else listaAg = listaAgendas;

	auxiliar = listaAg->INICIO;
	while (auxiliar!=NULL) 
	{
		if(i == numLista) return auxiliar;		
		auxiliar = auxiliar->siguiente;
		i++;
	}

	return NULL;

}

void mostrar_listaSimple(int num_agenda)
{
	AGM * agenda_actual;
	NLS * auxiliar;
	LTASIM *lista_actual;

	if(isEmpty(listaAgendas)==0){ 
		puts("INFO: No se pueden mostrar los sub-elementos ---> Lista de agendas vacia.");
	}else{
		agenda_actual = (AGM *)malloc(sizeof(AGM));
		agenda_actual = obtener_agenda(NULL, num_agenda);
		lista_actual = (LTASIM *)malloc(sizeof(LTASIM));
		lista_actual = agenda_actual->lista_simple;

		if(lista_actual->tam > 0){
			printf("\nID: %d  -  Especialidad: %s\n", num_agenda, agenda_actual->especialidad);
			auxiliar = agenda_actual->lista_simple->INICIO;
			while (auxiliar!=NULL) 
			{
				printf("Codigo del medico:  %d\n", auxiliar->codigo_medico);
				printf("Fecha de atencion: %s\n", auxiliar->str_fecha);
				printf("Cantidad de turnos libres: %d\n", auxiliar->turnos_libres);
				printf("Cantidad de turnos ocupados: %d\n\n", auxiliar->turnos_ocupados);
				auxiliar = auxiliar->siguiente;
			}
		}else{
			printf("INFO: La agenda %d aun no contiene elementos.\n", num_agenda);
		}
	}
	puts("Presione cualquier tecla para continuar...");
	fflush(stdin);
    getchar();
}

void eliminar_elementoLSimple(int num_agenda, int cod_medico)
{
	AGM * agenda_actual;
	NLS * respaldo;
	NLS * auxiliar;
	LTASIM *lista_actual;

	if(isEmpty(listaAgendas)==0){ 
		puts("INFO: No se pueden eliminar los sub-elementos ---> Lista de agendas vacia.");
	}else{
		agenda_actual = (AGM *)malloc(sizeof(AGM));
		agenda_actual = obtener_agenda(NULL, num_agenda);
		lista_actual = (LTASIM *)malloc(sizeof(LTASIM));
		lista_actual = agenda_actual->lista_simple;

		if(lista_actual->tam > 0){
			auxiliar = lista_actual->INICIO;
			while (auxiliar!=NULL) 
			{
				if(auxiliar->codigo_medico == cod_medico){
					respaldo->siguiente = auxiliar->siguiente;
					lista_actual->tam -= 1;
					free(auxiliar);
					printf("INFO: El medico: %d ha sido borrado de la lista num: %d - Especialidad '%s'\n", cod_medico, num_agenda, agenda_actual->especialidad);
					break;
				}
				respaldo = auxiliar;
				auxiliar = auxiliar->siguiente;
			}
		}else{
			printf("INFO: La agenda %d aun no contiene elementos.\n", num_agenda);
		}
	}
	puts("Presione cualquier tecla para continuar...");
	fflush(stdin);
    getchar();
}