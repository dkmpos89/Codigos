/* Bloque de identificacion de Sistema Operativo : 
* Sirve para setear variables usadas de forma diferente 
* en Linux y Windows
*/
#ifdef __unix__  
    #define OS_Windows 0
	#define OS_Clear "clear"
#elif defined(_WIN32) || defined(WIN32)
	#define OS_Windows 1
	#define OS_Clear "cls"
#endif
/* End ... */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


/* Declaracion de struct */
typedef struct NodoLTASIM
{
	int codigo;
	time_t fecha_atencion;
	int turnos_libres;
	int turnos_ocupados;
	struct NodoLTASIM *siguiente;
}NLS;

typedef struct listaSimple
{
	NLS *INICIO;
	NLS *FIN;
	int tam;
}LTASIM;

typedef struct AgendaMedica
{
   time_t fechaInicio;
   time_t fechaFin;
   char *especialidad;
   LTASIM  *lista_simple;
   struct AgendaMedica *siguiente;
}AGM;

typedef struct ListadoAgendasMedicas
{
	AGM *INICIO;
	AGM *FIN;
	int tam;// tamaño de la lista
}LAGM;



/* Declaracion de funciones */
void mostrarOpciones();
struct AgendaMedica *crearNuevaAgenda(char[], char[], char[]);
void setFecha(struct tm *, time_t *, char[]);
LAGM *crearLista();
LTASIM *crearListaSimple();
NLS *crearNodoLTASIM(int, char[], int, int);
void insertarAgenda(LAGM *, AGM *);
void eliminarAgenda(LAGM *);
int isEmpty(LAGM *listaAg);
void mostrar_listaAgendas(LAGM *listaAg);
void anadir_elementoAg();


/*  variables globales y constantes */
const char *SALIR = "1";
LAGM *listaAgendas;


/* Main del programa - Funcion principal */
int main()
{	
	/* Inicializacion de lista de Agendas que es una variable global */
	listaAgendas = crearLista();
	char opcion;

	/* Inserciones de prueba */
	struct AgendaMedica *Agenda1 = crearNuevaAgenda("08-01-2016", "18-01-2016", "Anatomia");
	if (Agenda1!=NULL) insertarAgenda(listaAgendas, Agenda1);
	
	struct AgendaMedica *Agenda2 = crearNuevaAgenda("19-08-2016", "29-08-2016", "Radiologia");
	if (Agenda2!=NULL) insertarAgenda(listaAgendas, Agenda2);
	/* Fin del bloque de Inserciones de prueba - Eliminar despues para version FINAL */

     do {
         mostrarOpciones();
         opcion = getch();
             switch ( opcion ) {
                case '1': exit( 1 );
                        break;
                case '2':  anadir_elementoAg();
                        break;
                case '3': eliminarAgenda(listaAgendas);
                        break;
                case '4': mostrar_listaAgendas(listaAgendas);
                		break;
                case '5': printf("consultando disponibilidad de turnos!..... :)");
                		getch();
                		break;
                default: break;
             }
     } while (opcion != *SALIR);

	return 0;
}
/* End of main() */


/* Implementacion de las funciones */
void mostrarOpciones()
{
	system(OS_Clear);
	puts("  ===========================================  ");
	puts("       M E N U    D E    O P C I O N E S       ");
	puts("  ===========================================  ");
	puts("  ===========================================  ");
	puts("1.- Salir\n");
	puts("2.- Ingresar Agenda Medica\n");
	puts("3.- Borrar Agenda Medica\n");
	puts("4.- Mostrar lista de Agendas\n");
	puts("5.- Consultar disponibilidad de turno\n\n");
	puts("Ingrese una opcion: ");
}

struct AgendaMedica *crearNuevaAgenda(char fI[], char fF[], char espec[])
{
	struct AgendaMedica *pAG = malloc(sizeof(struct AgendaMedica));
	pAG->especialidad = (char *)malloc(20*sizeof(char));
	pAG->siguiente = NULL;

	struct listaSimple *lS = malloc(sizeof(struct listaSimple));
	lS = crearListaSimple();

	/* Variables de la libreria time.h usadas para manejar las fechas */
	struct tm str_fechaI;
    time_t fechaI;
    setFecha(&str_fechaI, &fechaI, fI);
    
    struct tm str_fechaF;
    time_t fechaF;
    setFecha(&str_fechaF, &fechaF, fF);
    
    /* Se asignan los valores a las varibles de tipo time_t */      
	pAG->fechaInicio = fechaI;
	pAG->fechaFin = fechaF;
	strcpy(pAG->especialidad,espec);

	/* Se verifican los rangos de las fechas si son validos y se mustra un mensaje de ERROR*/
	double rango = difftime(fechaF, fechaI);
	if(rango<=0) {
		printf("Rango de fechas no valido: %f dias.\n", rango/(24*3600));  // la variable rango esta en segundos por eso se divide para convertirla en dias. 
		getch();
		free(pAG);
		return NULL;
	}
	puts("Nueva agenda creada con exito!... Presione cualquier tecla para continuar.");
	getch();
	return pAG;
}

void setFecha(struct tm *tlocal, time_t *tiempo, char fecha[10])
{
	*tiempo = time(0);
	tlocal = localtime(tiempo);
	char *str = (char *)malloc(10*sizeof(char));
	strcpy(str,fecha);
	const char s[2]="-";
	
	int numbday = atoi(strtok(str, s));
	int numbmonth = atoi(strtok(NULL, s))-1;
	int numbyear = atoi(strtok(NULL, s));
	
	tlocal->tm_mday = numbday;	
	tlocal->tm_mon = numbmonth;
	//tlocal->tm_year = numbyear;

	*tiempo = mktime(tlocal);	

}

/* Crea una lista de Agendas vacia y le asigna memoria */
LAGM *crearLista()
{
	LAGM *listaAgendas = (LAGM *)malloc(sizeof(LAGM));
	listaAgendas->INICIO = NULL;
	listaAgendas->FIN = NULL;
	listaAgendas->tam = 0;

	return listaAgendas;
}

LTASIM *crearListaSimple()
{
	LTASIM *listaNueva = (LTASIM *)malloc(sizeof(LTASIM));
	listaNueva->INICIO = NULL;
	listaNueva->FIN = NULL;
	listaNueva->tam = 0;

	return listaNueva;
}

NLS *crearNodoLTASIM(int codigo, char fecha_at[10], int t_disp, int t_ocup)
{
	NLS *nodo = (NLS *)malloc(sizeof(NLS));
	nodo->siguiente = NULL;

}

/* inserta un elemento Agenda en una lista de Agendas */
void insertarAgenda(LAGM *listaAg, AGM *agMed)
{
	if(listaAg!=NULL && agMed!=NULL)
	{
		if (isEmpty(listaAg)==0)
		{
			listaAg->INICIO = agMed;
			listaAg->FIN = agMed;
		}else{
			listaAg->FIN->siguiente = agMed;
			listaAg->FIN = agMed;
		}
		listaAg->tam += 1; // cada vez que se inserta se incrementa el contador de elementos de la lista.
	}else
		printf("ERROR: No se puede insertar el elemento en la lista.\n");
}

/* inserta un elemento Agenda en una lista de Agendas */
void eliminarAgenda(LAGM *listaAg)
{
	puts("Ingrese el numero de la agenda que se va a eliminar: ");
	char *inp = (char *)malloc(100*sizeof(char));
	scanf("%s", inp);
	int n = atoi(inp);

	AGM *nodo = NULL;
	AGM *agAux = NULL;

	if(listaAg->INICIO!=NULL && n>0 && n<=listaAg->tam)
	{
		/*  Bloque para el caso que se quiera eliminar el primer elemento */
		if (n==1){
			agAux = listaAg->INICIO;
			if(listaAg->tam==1){
				listaAg->INICIO = NULL;
				listaAg->FIN = NULL;
				free(agAux);
				puts("Registro Eliminado con exito!!\n" );
				puts("Presione cualquier tecla para continuar...");
				getch();
				return;
			}else{
				listaAg->INICIO = listaAg->INICIO->siguiente;
				free(agAux);
				puts("Registro Eliminado con exito!!\n" );
				puts("Presione cualquier tecla para continuar...");
				getch();
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
				puts("Registro Eliminado con exito!!\n" );
				break;
			} 
			nodo = nodo->siguiente;
		}
	}else{
		printf("ERROR: No se puede eliminar el elemento %d de la lista.\n", n);
	}
	puts("Presione cualquier tecla para continuar...");
	getch();
}

/* Verifica si la lista esta vacia */
int isEmpty(LAGM *listaAg)
{
	int cont = 0;
	if (listaAg!=NULL)
	{
		AGM *agAux = listaAg->INICIO;
		while(agAux!=NULL){
			agAux = agAux->siguiente;
			cont++;
		}
	}
	
	return cont;
}

void mostrar_listaAgendas(LAGM *listaAg)
{
	AGM *auxiliar = malloc(sizeof(AGM)); /* lo usamos para recorrer la lista */
	int i = 0;
	int cont = 1;

	char * fechaI = (char *)malloc(10*sizeof(char));
	char * fechaF= (char *)malloc(10*sizeof(char));

	auxiliar = listaAg->INICIO;
	printf("\nMostrando la lista completa:\n");
	while (auxiliar!=NULL) 
	{
		printf( "%d - Especialidad: %s\n", cont,auxiliar->especialidad);
		fechaI = ctime(&(auxiliar->fechaInicio));
		printf("Fecha Inicio: %s", fechaI);
		fechaF = ctime(&(auxiliar->fechaFin));
		printf("Fecha de Termino: %s\n", fechaF);

		auxiliar = auxiliar->siguiente;
		i++;
		cont++;
	}
	if (i==0) printf( "\nLa lista esta vacia!!\n" );
	free(auxiliar);
	puts("Presione cualquier tecla para continuar...");
	getch();
}

void anadir_elementoAg()
{
	AGM *nuevo;
	char f1[20], f2[20], esp[20];

	printf("\nNueva agenda Medica:\n");
	printf("Especialidad:	"); fflush(stdout);
	gets(esp);
	printf("Fecha de Inicio-->	(dd-mm-yyyy) : "); fflush(stdout);
	gets(f1);
	printf("Fecha de Termino->	(dd-mm-yyyy) : "); fflush(stdout);
	gets(f2);

	if (strlen(f1)==10 && strlen(f2)==10)
	{
		nuevo = crearNuevaAgenda(f1,f2,esp);
		insertarAgenda(listaAgendas, nuevo);
	}else{
		puts("ERROR: Formato de fechas incorrecto!");
		getch();
	}
	
}



/*


	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128];
	strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
	printf("%s\n",output);

	Anatomía
	Patológica	 	
 	Anestesiología y Reanimación
 	Cirugía General
 	Cirugía Cardiovascular
 	Cirugía Pediátrica	 	 
 	Cirugía Digestiva
 	Dermatología	 	 
 	Cirugía de Tórax

 	 pKeyboard = malloc(sizeof(struct MyStruct));
 	 
*/
