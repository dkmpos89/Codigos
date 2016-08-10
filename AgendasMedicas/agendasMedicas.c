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


/*  variables globales y constantes */
const int SI = 1;
const int NO = 0;
int salir = 0;
int tamListaAgendas = 0;// tamaño de la lista de agendas


/* Declaracion de struct */
typedef struct AgendaMedica
{
   time_t fechaInicio;
   time_t fechaFin;
   char *especialidad;

   //  *lista_simple;

   struct AgendaMedica *siguiente;
}AGM;

typedef struct ListadoAgendasMedicas
{
	AGM *INICIO;
	AGM *FIN;
}LAGM;



/* Declaracion de funciones */
void mostrarOpciones();
struct AgendaMedica *crearNuevaAgenda(char[], char[], char[]);
void setFecha(struct tm *, time_t *, char[]);
LAGM *crearLista();
void insertarAgenda(LAGM *, AGM *);
void eliminarAgenda(LAGM *, int n);
int isEmpty(LAGM *listaAg);




/* Main del programa - Funcion principal */
int main()
{	
	
	LAGM *listaAgendas = crearLista();

	struct AgendaMedica *Agenda1 = crearNuevaAgenda("08-01-2016", "18-01-2016", "Anatomia");
	if (Agenda1!=NULL)
	{
		printf("%s\n", (Agenda1->especialidad));
		printf("%s\n", ctime(&(Agenda1->fechaInicio)));
		printf("%s\n", ctime(&(Agenda1->fechaFin)));

		insertarAgenda(listaAgendas, Agenda1);
	}

	
	struct AgendaMedica *Agenda2 = crearNuevaAgenda("19-08-2016", "29-08-2016", "Radiologia");
	if (Agenda2!=NULL)
	{
		printf("%s\n", (Agenda2->especialidad));
		printf("%s\n", ctime(&(Agenda2->fechaInicio)));
		printf("%s\n", ctime(&(Agenda2->fechaFin)));

		insertarAgenda(listaAgendas, Agenda2);
	}

	printf("Numero de elementos de la lista de Agendas: %d\n", tamListaAgendas);

	/*
	do{
		mostrarOpciones();
	}while(salir!=SI);
	*/

	return 0;
}
/* End of main() */


/* implementacion de las funciones */
void mostrarOpciones()
{
	char *opcion = malloc(sizeof(char*)*10);
	int nopcion = 0;
	do{
		system(OS_Clear);
		puts("  ===========================================  ");
		puts("       M E N U    D E    O P C I O N E S       ");
		puts("  ===========================================  ");
		puts("  ===========================================  ");
		printf("Ingrese una opcion: ");
		gets(opcion);
		nopcion = atoi(opcion);
	}while (nopcion<0 || nopcion>9);

	if(nopcion==1) {salir = SI; return;}
	else{ printf("Trabajando en la opcion seleccionada!\n");}
	
	/* 
	aqui va el Bloque de opciones con llamadas a otras funciones.
	.	.
	.	.

	*/
}

struct AgendaMedica *crearNuevaAgenda(char fI[], char fF[], char espec[])
{
	struct AgendaMedica *pAG;
	pAG = malloc(sizeof(struct AgendaMedica));
	pAG->especialidad = (char *)malloc(50*sizeof(char));
	pAG->siguiente = NULL;

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
	pAG->especialidad = espec;

	/* Se verifican los rangos de las fechas si son validos y se mustra un mensaje de ERROR*/
	double rango = difftime(fechaF, fechaI);
	if(rango<=0) {
		printf("Rango de fechas no valido: %f dias.\n", rango/(24*3600));  // la variable rango esta en segundos por eso se divide para convertirla en dias. 
		free(pAG);
		return NULL;
	}

	return pAG;
}

void setFecha(struct tm *tlocal, time_t *tiempo, char fecha[8])
{
	*tiempo = time(0);
	tlocal = localtime(tiempo);
	char *str = (char *)malloc(sizeof(char*)*8);
	strcpy(str,fecha);
	const char s[2]="-";
	
	int numbday = atoi(strtok(str, s));
	int numbmonth = atoi(strtok(NULL, s))-1;
	int numbyear = atoi(strtok(NULL, s));
	
	tlocal->tm_mday = numbday;	
	tlocal->tm_mon = numbmonth;
	//tlocal->tm_year = numbyear;

//	char output[128];
//	strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
//	printf("%s\n",output);
	
	*tiempo = mktime(tlocal);	

}

/* Crea una lista de Agendas vacia y le asigna memoria */
LAGM *crearLista()
{
	LAGM *listaAgendas = malloc(sizeof(LAGM));
	listaAgendas->INICIO = NULL;
	listaAgendas->FIN = NULL;

	return listaAgendas;
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
		tamListaAgendas++; // cada vez que se inserta se incrementa el contador de elementos de la lista general. (Variable Global)
	}else
		printf("ERROR: No se puede insertar el elemento en la lista.\n");
}

/* inserta un elemento Agenda en una lista de Agendas */
void eliminarAgenda(LAGM *listaAg, int n)
{
	if(listaAg!=NULL && n>0 && n<=tamListaAgendas)
	{
		if (n==1 && tamListaAgendas==1)
		{
			listaAg->INICIO = NULL;
			listaAg->FIN = NULL;
			return;
		}

		AGM *actual = listaAg->INICIO;
		AGM *agAux = NULL;
		for (int i = 1; i <= tamListaAgendas; ++i)
		{
			if(i==n){
				agAux = actual->siguiente;
				break;
			} 
			actual = actual->siguiente;
		}
	}else
		printf("ERROR: No se puede eliminar el elemento %d de la lista.\n", n);
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
