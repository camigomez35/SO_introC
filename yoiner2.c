/*
================================================================================
Name         : eval2_GomezYoiner.c
Author       : Yoiner Esteban Gomez Ayala
Version      : 1.0
Compilation  : gcc -Wall parcia2.c -o parcia2.out
Execution    : ./parcial.out
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Definición de constantes
*/
#define MAX_NOMBRE 20


/**
 * Definición de métodos
 */
void *reservarMemoria(int n,void *ptr, int tamanio);
void obtenerOpcionMenu(char *opcion);
void registrarProductos(int *num_productos);
void mostrarProductos(int *num_productos);
void mostrarProductosBusqueda(int *num_productos,char (*busqueda)[MAX_NOMBRE]);
void buscarProductos(int *num_productos);
int existenProductos(int *num_productos);
 
char (*nombres)[MAX_NOMBRE] = NULL;
int *cantidad = NULL;
 
int main(int argc, char const *argv[]) {
    int num_productos=0;
    char opcion = 'x';
    
    do {
        obtenerOpcionMenu(&opcion);
        switch (opcion) {
            case 'a':
                registrarProductos(&num_productos);
                break;
            case 'b':
                buscarProductos(&num_productos);
                //mostrarProductos(&num_productos);
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
        puts("No se puede reservar memoria.");
        exit(1);
    }
    return ptr;
}

void registrarProductos(int *num_productos) {
  int i = 0;
  int num_produc = 0;

  printf("Ingrese el numero de productos a registrar: ");
  setbuf(stdin, NULL);
  scanf("%d", &num_produc);
  nombres = ( char (*)[MAX_NOMBRE])reservarMemoria(*num_productos+num_produc,nombres, sizeof(char[MAX_NOMBRE]));
  cantidad = (int *)reservarMemoria(*num_productos+num_produc,(int *) cantidad, sizeof(int));
  if(nombres==NULL || cantidad==NULL){
        puts("registrarProductos");
  }
  for (i = *num_productos; i < *num_productos + num_produc; i++) {
        printf("\nNombre del producto #%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(nombres+i));
        printf("Cantidad: ");
        setbuf(stdin, NULL);
        scanf("%d", cantidad+i);
  }
  *num_productos += num_produc;
}

void mostrarProductos(int *num_productos) {
  int i = 0;
  printf("|%-25s|%-12s|\n", "Nombre", "Cantidad");
  for (i = 0; i < *num_productos; i++) {
      printf("|%-25s|%-12d|\n",(char *) (nombres+i), *(cantidad+i));
  }
}

int existenProductos(int *num_productos) {
    if (*num_productos==0) {
        return 0;
    }
    return 1;
}

void buscarProductos(int *num_productos){
    char busqueda[MAX_NOMBRE] = "";
    int resultado = 0;
    
    if (!existenProductos(num_productos)) {
      printf("No hay productos para mostrar.\n");
      return;
    }
    printf("\nIngrese la busqueda: ");
    setbuf(stdin, NULL);
    scanf("%s", (char *)busqueda);
    resultado = strcmp(busqueda,"all");
    if(resultado==0){
        mostrarProductos(num_productos);
    } else{
        mostrarProductosBusqueda(num_productos,(char (*)[MAX_NOMBRE])busqueda);
    }
}

void mostrarProductosBusqueda(int *num_productos,char (*busqueda)[MAX_NOMBRE]){
    int i = 0;
    char *ptr = NULL;
    printf("|%-25s|%-12s|\n", "Nombre", "Cantidad");
    for (i = 0; i < *num_productos; i++) {
        ptr = strstr((char *) (nombres+i), (char *) busqueda);
        if(ptr != NULL){
            printf("|%-25s|%-12d|\n",(char *) (nombres+i), *(cantidad+i));	
        }
    }
}