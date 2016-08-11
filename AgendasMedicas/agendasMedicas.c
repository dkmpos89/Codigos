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
	int codigo_medico;
	time_t fecha_atencion;
	char *str_fecha;
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



/* Declaracion de funciones */
void mostrarOpciones();
struct AgendaMedica *crearNuevaAgenda(char[], char[], char[]);
void setFecha(struct tm *, time_t *, char[]);
LTAGM *crearLista();
LTASIM *crearListaSimple();
NLS *crearNodoLTASIM(int, char[], int, int);
void insertarAgenda(LTAGM *, AGM *);
void insertarNodo(LTASIM *, NLS *);
void eliminarAgenda(LTAGM *);
int isEmpty(LTAGM *);
void mostrar_listaAgendas(LTAGM *);
void anadir_elementoAg();
void ingresar_elementoLS();
AGM *obtener_agenda(LTAGM *, int);
int verificar_turno(int, int, char[]);

/*  variables globales y constantes */
const char *SALIR = "1";	// Variable de control
LTAGM *listaAgendas;		// Lista general de agendas.
const char s[2]="-";		// delimitador de las fechas

/* Main del programa - Funcion principal */
int main()
{	
	/* Inicializacion de lista de Agendas que es una variable global */
	listaAgendas = crearLista();
	char opcion;
	int vt = -1; // variable para verificar_turnos:  0 | -1
	int num_agenda = 0, code_medico = 0;
	char fecha_consulta[10];


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
                case '1': printf("BYE!"); 
                		exit( 1 );
                        break;
                case '2':  anadir_elementoAg();
                        break;
                case '3': eliminarAgenda(listaAgendas);
                        break;
                case '4': mostrar_listaAgendas(listaAgendas);
                		break;
                case '5': ingresar_elementoLS();
                		break;
                case '6': 
                		puts("Ingrese el ID de la agenda: ");
                		scanf("%d", &num_agenda);
                		puts("Ingrese el codigo del medico: ");
                		scanf("%d", &code_medico);
                		puts("Ingrese la fecha --> (dd-mm-yyyy): ");
                		scanf("%s", &fecha_consulta);
                		vt = verificar_turno(num_agenda, code_medico, fecha_consulta);
                		if(vt == 0) 
                			puts("Turno Disponible...  :)");
                		else
                			puts("Turno NO Disponible... :(");
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
	puts("2.- Ingresar nueva agenda Medica\n");
	puts("3.- Borrar Agenda Medica\n");
	puts("4.- Mostrar lista de Agendas\n");
	puts("5.- Ingresar elemento a lista_simple\n");
	puts("6.- Consultar disponibilidad de turno\n\n");
	puts("Ingrese una opcion: ");
}

struct AgendaMedica *crearNuevaAgenda(char fI[], char fF[], char espec[])
{
	struct AgendaMedica *pAG = malloc(sizeof(struct AgendaMedica));
	pAG->especialidad = (char *)malloc(20*sizeof(char));
	pAG->str_fecha_I = (char *)malloc(20*sizeof(char));
	pAG->str_fecha_F = (char *)malloc(20*sizeof(char));
	pAG->siguiente = NULL;

	struct listaSimple *lS = malloc(sizeof(struct listaSimple));
	lS = crearListaSimple();
	pAG->lista_simple = lS;

	/* Variables de la libreria time.h usadas para manejar las fechas */
	struct tm str_fechaI;
    time_t fechaI;
    setFecha(&str_fechaI, &fechaI, fI);
    strcpy(pAG->str_fecha_I, fI);

    struct tm str_fechaF;
    time_t fechaF;
    setFecha(&str_fechaF, &fechaF, fF);
    strcpy(pAG->str_fecha_F, fF);

    /* Se asignan los valores a las varibles de tipo time_t */      
	pAG->fechaInicio = fechaI;
	pAG->fechaFin = fechaF;
	strcpy(pAG->especialidad,espec);

	/* Se verifican los rangos de las fechas si son validos y se mustra un mensaje de ERROR*/
	double rango = difftime(fechaF, fechaI);
	if(rango<=0) {
		printf("ERROR: Rango de fechas no valido: %f dias.\n", rango/(24*3600));  // la variable rango esta en segundos por eso se divide para convertirla en dias. 
		getch();
		free(pAG);
		return NULL;
	}
	puts("\nSUCCESS: Nueva agenda creada con exito!...\nPresione cualquier tecla para continuar.");
	return pAG;
}

NLS *crearNodoLTASIM(int cod, char fecha_at[], int t_disp, int t_ocup)
{
	NLS *nodo = (NLS *)malloc(sizeof(NLS));
	nodo->siguiente = NULL;
	nodo->str_fecha = (char *)malloc(20*sizeof(char));
	nodo->codigo_medico = cod;

	struct tm strFecha;
    time_t fecha;
    setFecha(&strFecha, &fecha, fecha_at);
    strcpy(nodo->str_fecha, fecha_at);

	nodo->fecha_atencion = fecha;

	nodo->turnos_libres = t_disp;
	nodo->turnos_ocupados = t_ocup;

	return nodo; 
}

void setFecha(struct tm *tlocal, time_t *tiempo, char fecha[10])
{
	char *str = (char *)malloc(10*sizeof(char));
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

LTASIM *crearListaSimple()
{
	LTASIM *listaNueva = (LTASIM *)malloc(sizeof(LTASIM));
	listaNueva->INICIO = NULL;
	listaNueva->FIN = NULL;
	listaNueva->tam = 0;

	return listaNueva;
}

/* inserta un elemento Agenda en una lista de Agendas */
void insertarAgenda(LTAGM *listaAg, AGM *agMed)
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

/* inserta un elemento NODO en una lista_simple de una Agenda */
void insertarNodo(LTASIM *listaSim, NLS *Nod)
{
	if(listaSim!=NULL && Nod!=NULL)
	{
		if (listaSim->INICIO==NULL)
		{
			listaSim->INICIO = Nod;
			listaSim->FIN = Nod;
		}else{
			listaSim->FIN->siguiente = Nod;
			listaSim->FIN = Nod;
		}
		listaSim->tam += 1; // cada vez que se inserta se incrementa el contador de elementos de la lista.
	}else{
		printf("ERROR: No se puede insertar el elemento en la lista.\n");
		return;
	}
	puts("\nSUCCESS: Elemento creado con exito!");
}

/* inserta un elemento Agenda en una lista de Agendas */
void eliminarAgenda(LTAGM *listaAg)
{
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
			agAux = listaAg->INICIO;
			if(listaAg->tam==1){
				listaAg->INICIO = NULL;
				listaAg->FIN = NULL;
				free(agAux);
				puts("SUCCESS: Registro Eliminado!\n" );
				puts("Presione cualquier tecla para continuar...");
				getch();
				return;
			}else{
				listaAg->INICIO = listaAg->INICIO->siguiente;
				free(agAux);
				puts("SUCCESS: Registro Eliminado!\n" );
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
				puts("SUCCESS: Registro Eliminado!\n" );
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
int isEmpty(LTAGM *listaAg)
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

void mostrar_listaAgendas(LTAGM *listaAg)
{
	AGM *auxiliar = malloc(sizeof(AGM)); /* lo usamos para recorrer la lista */
	int i = 0;
	int cont = 1;

	//char * fechaI = (char *)malloc(10*sizeof(char));
	//char * fechaF= (char *)malloc(10*sizeof(char));

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
	getch();
}

void ingresar_elementoLS()
{
	AGM * agenda_actual = (AGM *)malloc(sizeof(AGM));
	NLS *nuevo = (NLS *)malloc(sizeof(NLS));
	int numLista, cod_med, turnos_libres, turnos_ocupados;
	char fecha_atencion[20];

	printf("\nIngrese numero de la Lista en la que se va a insertar: ");
	scanf("%d", &numLista);
	printf("Ingrese el codigo del medico:	"); fflush(stdout);
	scanf("%d", &cod_med);
	printf("Ingrese la fecha de atencion -->(dd-mm-yyyy): "); fflush(stdout);
	scanf("%s", &fecha_atencion);
	printf("Ingrese la cantidad de turnos libres: "); fflush(stdout);
	scanf("%d", &turnos_libres);
	printf("Ingrese la cantidad de turnos ocupados: "); fflush(stdout);
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
	getch();
}

int verificar_turno(int num_agenda, int cod_medico, char fecha_atencion[])
{
	AGM * agenda_actual = (AGM *)malloc(sizeof(AGM));
	agenda_actual = obtener_agenda(NULL, num_agenda);

	NLS * auxiliar;

	auxiliar = agenda_actual->lista_simple->INICIO;
	while (auxiliar!=NULL) 
	{
		if(auxiliar->codigo_medico == cod_medico) {
			puts("Encontre al medico!");
			if(*auxiliar->str_fecha = fecha_atencion && auxiliar->turnos_libres>0)
				return 0;
		}
		auxiliar = auxiliar->siguiente;
	}

	return -1;
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


/*
	insertarNodo(LTASIM *listaSim, NLS *Nod)


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
