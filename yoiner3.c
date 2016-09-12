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
 * Definición de estructura
 */
typedef struct {
  char nombre[20];
  int precio;
  int cantidad;
} Producto;


/**
 * Definición de métodos
 */
FILE *abrirArchivo(char *modo);
int contarLineasArchivo(FILE *in_file);
void *reservarMemoria(int n,void *ptr, int tamanio);
void obtenerOpcionMenu(char *opcion);
Producto *obtenerDatos(FILE *in_file, Producto *ptrProduct, int numLines);
Producto *registrarProductos(int *num_productos);
void mostrarProductos(int *num_productos, Producto *producto);
void mostrarProductosBusqueda(int *num_productos,Producto *producto,char (*busqueda)[MAX_NOMBRE]);
void buscarProductos(int *num_productos, Producto *producto);
int existenProductos(int *num_productos);

const char NOMBRE_ARC[] = "inventario.txt"; 
 
int main(int argc, char const *argv[]) {
    int num_productos=0;
    char opcion = 'x';
    FILE *archivo;
    Producto *producto = NULL;
    Producto *product = NULL;
    
    abrirArchivo("r+");
    
    do {
        obtenerOpcionMenu(&opcion);
        switch (opcion) {
            case 'a':
                //producto = registrarProductos(&num_productos);
                archivo = abrirArchivo("r");
                
                num_productos = contarLineasArchivo(archivo);
                num_productos = num_productos/3;
            
                producto = obtenerDatos(archivo, producto, num_productos);
                break;
            case 'b':
                buscarProductos(&num_productos,producto);
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
    fclose(archivo);
    free(producto);
    free(product);

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

Producto *registrarProductos(int *num_productos) {
  int i = 0;
  int num_produc = 0;
  Producto *ptr = NULL;

  printf("Ingrese el numero de productos a registrar: ");
  setbuf(stdin, NULL);
  scanf("%d", &num_produc);
  ptr = (Producto *)reservarMemoria(*num_productos+num_produc,ptr, sizeof(Producto));

  for (i = *num_productos; i < *num_productos + num_produc; i++) {
        printf("\nNombre del producto #%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(ptr+i)->nombre);
        printf("Cantidad: ");
        setbuf(stdin, NULL);
        scanf("%d", &(ptr+i)->cantidad);
  }
  *num_productos += num_produc;
  
  return ptr;
}

Producto *obtenerDatos(FILE *in_file, Producto *ptrProduct, int numLines){
	int i;
	ptrProduct = malloc(sizeof(Producto) * numLines);
	
	for(i =0 ; i<numLines; i++){
		fscanf(in_file, "%s", ptrProduct->nombre);
		fscanf(in_file, "%d", &ptrProduct->cantidad);
		fscanf(in_file, "%d", &ptrProduct->precio);

		ptrProduct++;
	}
	return (ptrProduct-numLines);
}

void mostrarProductos(int *num_productos, Producto *producto) {
  int i = 0;
  printf("|%-25s|%-12s|\n", "Nombre", "Cantidad");
  for (i = 0; i < *num_productos; i++) {
      printf("|%-25s|%-12d|\n",producto->nombre, producto->cantidad);
      producto++;
  }
}

int existenProductos(int *num_productos) {
    if (*num_productos==0) {
        return 0;
    }
    return 1;
}

void buscarProductos(int *num_productos, Producto *producto){
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
        mostrarProductos(num_productos, producto);
    } else{
        mostrarProductosBusqueda(num_productos,producto,(char (*)[MAX_NOMBRE])busqueda);
    }
}

void mostrarProductosBusqueda(int *num_productos,Producto *producto,char (*busqueda)[MAX_NOMBRE]){
    int i = 0;
    char *ptr = NULL;
    printf("|%-25s|%-12s|\n", "Nombre", "Cantidad");
    for (i = 0; i < *num_productos; i++) {
        ptr = strstr((char *) producto->nombre, (char *) busqueda);
        if(ptr != NULL){
            printf("|%-25s|%-12d|\n",producto->nombre, producto->cantidad);	
        }
        producto++;
    }
}

FILE *abrirArchivo(char *modo) {
  FILE *file;

  file = fopen(NOMBRE_ARC, modo);

  // Validar si el archivo fue abierto
  if (!file) {
    printf("Error al abrir el archivo: %s\n", NOMBRE_ARC);
    exit(1);
  }

  return file;
}

int contarLineasArchivo(FILE *in_file){
	int ch=0;
	int lines=1;
	
	while ((ch = fgetc(in_file)) != EOF){
    	if (ch == '\n'){
    		lines++;
    	}
    }
    rewind(in_file);
	return lines;
}