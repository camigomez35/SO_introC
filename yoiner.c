/*
================================================================================
Name         : eval1_GomezYoiner.c
Author       : Yoiner Esteban Gomez Ayala
Version      : 1.0
Compilation  : gcc -Wall parcial.c -o parcial.out
Execution    : ./parcial.out
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Definición de constantes
 */
#define MAX_NOMBRE 20
    

 /**
 * Definición de métodos
 */
 void *reservarMemoria(int n,void *ptr, int tamanio);
 void obtenerOpcionMenu(char *opcion);
 void registrarProductos(char *(*nombres)[MAX_NOMBRE], int **cantidad);
 void mostrarProductos(char (*nombres)[MAX_NOMBRE], int *cantidad);
 int existenProductos();

int num_productos=0;

int main(int argc, char const *argv[]) {
	/* code */
    char opcion = 'x';
    char (*nombres)[MAX_NOMBRE] = NULL;
    int *cantidad = NULL;
    
    do {
        if(nombres==NULL || cantidad==NULL){
            puts("main");
        }
        obtenerOpcionMenu(&opcion);
        switch (opcion) {
            case 'a':
                registrarProductos(&nombres,&cantidad);
                break;
            case 'b':
                mostrarProductos(&nombres,&cantidad);
                break;
            case 'q':
                
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("La opcion '%c' no es valida. Volviendo al menu.\n", opcion);
                break;
        }
    } while(opcion != 'q');


	/* ===Liberar memoria=== */
   free(nombres);
   free(cantidad);

	return 0;
}


void obtenerOpcionMenu(char *opcion) {
  printf("\nMENU DE OPCIONES\n");
  printf("\ta) Agregar productos.\n");
  printf("\tb) Ver inventario.\n");
  printf("\tq) Salir del programa.\n");
  printf("Seleccione una opcion: ");
  setbuf(stdin, NULL);
  scanf("\n%c", opcion);
}

void *reservarMemoria(int n,void *ptr, int tamanio){
    ptr = (int *) realloc((void *)ptr, tamanio*n);
    if(ptr==NULL){
        puts("No se puede reservar memoria para los nombres");
    }
    return ptr;
}

void registrarProductos(char (*nombres)[MAX_NOMBRE], int *cantidad) {
  int i = 0;
  int num_produc = 0;

  printf("Ingrese el numero de productos a registrar: ");
  setbuf(stdin, NULL);
  scanf("%d", &num_produc);
  (*nombres)[MAX_NOMBRE] = *( char (*)[MAX_NOMBRE])reservarMemoria(num_productos+num_produc,nombres, sizeof(char[MAX_NOMBRE]));
  (*cantidad) = *(int *)reservarMemoria(num_productos+num_produc,(int *) cantidad, sizeof(int));
  if(nombres==NULL || cantidad==NULL){
        puts("registrarProductos");
  }
  for (i = num_productos; i < num_productos + num_produc; i++) {
        printf("\nNombre del producto #%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(nombres+i));
        printf("Cantidad: ");
        setbuf(stdin, NULL);
        scanf("%d", cantidad+i);
  }
  num_productos += num_produc;
  mostrarProductos(nombres,cantidad);
}

void mostrarProductos(char (*nombres)[MAX_NOMBRE], int *cantidad) {
  int i = 0;
  if (!existenProductos()) {
      printf("No hay productos para mostrar.\n");
      return;
  }
  printf("|%-25s|%-12s|\n", "Nombre", "Cantidad");
  for (i = 0; i < num_productos; i++) {
      printf("|%-25s|%-12d|\n",(char *) *(nombres+i), *(cantidad+i));
  }
}

int existenProductos() {
    if (num_productos) {
        return 1;
    }
    return 0;
}