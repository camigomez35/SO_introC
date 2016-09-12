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

/**
* Definición de constantes
*/
#define MAX_NOMBRE 20


/**
 * Definición de métodos
 */
void reservarMemoria(int n,void *ptr, int tamanio);
void obtenerOpcionMenu(char *opcion);
void registrarProductos(char (*nombres)[MAX_NOMBRE], int *cantidad);
void mostrarProductos(char (*nombres)[MAX_NOMBRE], int *cantidad);
int existenProductos();
 
char (*nombres)[MAX_NOMBRE] = NULL;
int *cantidad = NULL;
 
int main(int argc, char const *argv[]) {
int num_productos=0;
 
}