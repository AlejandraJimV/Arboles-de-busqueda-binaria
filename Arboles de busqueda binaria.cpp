/*
Elaborado por Alejandra Jiménez Venegas
Estructuras de Datos 
Este código es un ejemplo de cómo implementar un árbol de búsqueda binaria en C, con funcionalidades 
para manipular y visualizar el árbol. Es útil para entender las operaciones básicas de los árboles y 
cómo se pueden utilizar para gestionar datos de manera eficiente. */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <graphics.h>
#define color SetConsoleTextAttribute
#define TRUE 1
#define FALSE 0

/* Estructuras y tipos */
typedef struct _nodo {
   struct _nodo *izquierdo;
	 int dato;
   struct _nodo *derecho;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

int margen(int a, int b, int c, int d);
void mostrarArbol(Arbol raiz, int x, int y, int nivel);
void gotoxy(int x,int y);
void Insertar(Arbol *a, int dat);
void Borrar(Arbol *a, int dat);
int Buscar(Arbol a, int dat);
int Vacio(Arbol r);
int EsHoja(pNodo r);
int NumeroNodos(Arbol a, int* c);
int AlturaArbol(Arbol a, int* altura);
void InOrden(Arbol);
void encabezado();
void Podar(Arbol *a);
void auxContador(Arbol a, int*);
int menu();
void borrar();

int main(){
	Arbol ArbolInt=NULL;
	int a = DETECT, b;
	int opcion,num;
	do{
		margen(1, 1, 100, 25);
        opcion = menu();
        system("cls");
        switch (opcion) {
			case 1: 
					encabezado();
            		margen(1, 1, 100, 25);
					gotoxy(45,6); printf("Insertar");
					gotoxy(20, 8); printf("Ingrese el dato: ");
					scanf("%d",&num);
					Insertar(&ArbolInt, num);
					gotoxy(20, 10); printf("Estado actual del arbol: ");
					InOrden(ArbolInt);
					break;
			case 2: 
					encabezado();
	            	margen(1, 1, 100, 25);
					gotoxy(45,6); printf("Mostrar");
    				initgraph(&a, &b, (char*)("C:\\Dev-Cpp\\MinGW64\\lib"));
					mostrarArbol(ArbolInt, getmaxx()/2, 10 ,1 );
					break;
			case 3: 
					encabezado();
	            	margen(1, 1, 100, 25);
					gotoxy(45,6); printf("Buscar");
					gotoxy(20,8); printf("Ingrese el numero a buscar: ");
					scanf("%d",&num);
					Buscar(ArbolInt, num);
					gotoxy(20, 15); printf("Estado actual del arbol: ");
					InOrden(ArbolInt);
					break;  
			case 4: 
					encabezado();
            		margen(1, 1, 100, 25);
					gotoxy(45,6); printf("Eliminar");
					gotoxy(20, 8); printf("Ingrese el dato a eliminar: ");
					scanf("%d",&num);
					Borrar(&ArbolInt, num);
					gotoxy(20, 15); printf("Estado actual del arbol: ");
					InOrden(ArbolInt);
					break;
			case 5: 
					encabezado();
            		margen(1, 1, 100, 25);
					gotoxy(45,6); printf("Vaciar");
					Podar(&ArbolInt);
					gotoxy(35,10); printf("El arbol ha sido vaciado");
					break;   
			case 6: 
				encabezado();
            	margen(1, 1, 100, 25);
				gotoxy(38,13); printf("Saliendo del programa....");
				Sleep(800);
				system("cls");
			return 0;
			
			default: gotoxy(40,20); printf("La opcion ingresada es invalida");
		}
	borrar();
	}while(opcion != 6);
	
}

void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}  

//Agregar nodo/dato
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;

   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }
   
   if(!Vacio(actual)) return;
   //Si no hay padre se vuelve raiz 
   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
   }
   
   //Hijo izq
   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
   }
   //Hijo der
   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
  }
}

void mostrarArbol(Arbol raiz, int x, int y, int altura) {
    int radio = 25, mitadX = x, mitadY = y;
    
    // Coordenadas izquierda y derecha 
    int izquierdaX = x - (200 / (altura + 1));
    int izquierdaY = y + 100;
    int derechaX = x + (200 / (altura + 1));
    int derechaY = y + 100;
    char digito[50];

    if (raiz == NULL) {
        return;
    }
    
    circle(mitadX, mitadY, radio);
    sprintf(digito, "%d", raiz->dato);
    outtextxy(mitadX - 3, mitadY - 6, digito);

    // Línea izquierda
    if (raiz->izquierdo != NULL) {
        line(mitadX - radio, mitadY + radio, izquierdaX, izquierdaY - radio);
        mostrarArbol(raiz->izquierdo, izquierdaX, izquierdaY, altura + 1);
    }

    // Línea derecha
    if (raiz->derecho != NULL) {
        line(mitadX + radio, mitadY + radio, derechaX, derechaY - radio);
        mostrarArbol(raiz->derecho, derechaX, derechaY, altura + 1);
    }
}


//Borrar elemento
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *a;
   
   while(!Vacio(actual)) {
      if(dat == actual->dato) { 
         if(EsHoja(actual)) { 
            if(padre) //Si hay padre
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            free(actual); //Liberar
            gotoxy(35,10); printf("Elemento eliminado");
            actual = NULL;
            return;
         }
         else { //No es hoja
            padre = actual;
            if(actual->derecho) { //der
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            else { //izq
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else {
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   //si no se encuentra
   gotoxy(35,10); printf("Elemento no encontrado");
}

//Buscar
int Buscar(Arbol a, int dat)
{
   pNodo actual = a;

   while(!Vacio(actual)) {
      if(dat == actual->dato){
      	gotoxy(35,10); printf("Elemento encontrado en el arbol");
	  	return TRUE; 
	  } 
      else if(dat < actual->dato) actual = actual->izquierdo; /* Seguir */
      else if(dat > actual->dato) actual = actual->derecho;
   }
   gotoxy(35,10); printf("Elemento NO encontrado en el arbol");
   return FALSE;
}
int menu()
{
	encabezado();
    int op;
    gotoxy(45, 8);
    printf("Opciones:");
    gotoxy(40, 10);
    printf("1. Insertar");
    gotoxy(40, 11);
    printf("2. Mostrar");
    gotoxy(40, 12);
    printf("3. Buscar");
    gotoxy(40, 13);
    printf("4. Eliminar");
    gotoxy(40, 14);
    printf("5. Vaciar");
    gotoxy(40, 15);
    printf("6. Salir");
    gotoxy(40, 16);
    printf("Seleccione una opcion: ");
    scanf("%d", &op);

    return op;
}

void encabezado()
{
	margen(34, 2, 62, 4);
	gotoxy(35, 3);
	printf("ARBOLES DE BUSQUEDA BINARIA");
	
}

//Borrar nodos/ podar
void Podar(Arbol *a)
{
   if(*a) {
      Podar(&(*a)->izquierdo); //B izq 
      Podar(&(*a)->derecho); //B der
      free(*a);
      *a = NULL;
   }
}

void InOrden(Arbol a)
{
   if(a->izquierdo) InOrden(a->izquierdo);
   printf("%d, ", a->dato);
   if(a->derecho) InOrden(a->derecho);
}


//Altura 
int Altura(Arbol a, int dat)
{
   int altura = 0;
   pNodo actual = a;

   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; /* encontrado: devolver altura */
      else {
         altura++;
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1;
}

int NumeroNodos(Arbol a, int *cont)
{
   *cont = 0;
   auxContador(a, cont); 
   return *cont;
}

void auxContador(Arbol nodo, int *c)
{
   (*c)++; 
   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}

void borrar()
{
	gotoxy(60,25);
		system("pause");
		system("cls");
}


int Vacio(Arbol r)
{
   return r==NULL;
}

int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}


int margen(int a, int b, int c, int d) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 13);
    int j, k;
    j = a;
    gotoxy(a - 1, b);
    printf("%c", 201);
    gotoxy(a - 1, d);
    printf("%c", 200);
    for (a; a <= c; a++) {
        gotoxy(a, b);
        printf("%c", 205);
        gotoxy(a, d);
        printf("%c", 205);
    }
    gotoxy(a, b);
    printf("%c", 187);
    gotoxy(a, d);
    printf("%c", 188);
    k = b + 1;
    for (k; k <= (d - 1); k++) {
        gotoxy(j - 1, k);
        printf("%c", 186);
        gotoxy(a, k);
        printf("%c", 186);
    }
    color(hConsole, 7);
}

