/*
================================================================================
Name         : eval2_GomezMAria.c
Author       : Maria Camila Gomez Restrepo
Version      : 1.0
Compilation  : gcc -Wall eval2_GomezMaria.c -o eval2_GomezMaria.out
Execution    : ./eval2_GomezMaria.out
================================================================================
*/

/* Including headers or libraries. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MAX_CHARS_NAME 25


/* Definition of macros and constants. */


/* Definition of structures. */
struct product {
	char name[MAX_CHARS_NAME];
	int stock;
	int price;
 };

/* Declaring functions. */

 //Menu
void menu(char *option);

//Para guardar desde archivo
FILE *openFile(char *fileName, char *mode);
struct product *getData(FILE *in_file);
struct product *increaseProduct(struct product *producto);
void lineProcess(char *line, struct product *producto);

//Para guardar desde consola
struct product *addProducts( int addProduct, struct product *producto, FILE *in_file);

//Para imprimir
void print(struct product *producto);
void printDataAll(struct product *producto);
void printData(struct product *producto, char search[MAX_CHARS_NAME]);

/* Global variables. */
int count = 0;

/* Main function. */
int main (int argc, char *argv[]) {
	FILE *in_file;
	struct product *producto =NULL;
	int addProduct;
	char option = ' ';

	if (argc != 2) {
	    puts("Error al ejecutar, debes hacerlo de la siguiente forma");
	    printf("%s <archivo_entrada> \n", argv[0]);
	    return 1;
	}

	// Abrir los 3 archivos
	in_file = openFile(argv[1], "a+");
	producto = getData(in_file);
	
	do {
    menu(&option);

    switch(option) {
      case 'a':
	puts("¿Cuantos productos desea agregar?");
            setbuf(stdin, NULL);
            scanf("%d", &addProduct);
            producto = addProducts(addProduct, producto, in_file);
       break;
      case 'b':
      		print(producto);
        break;
      case 'q':
        puts("Saliendo del programa...");
        break;
      default:
        puts("Opción no valida, intenta de nuevo.");
        break;
    }
  } while(option != 'q');


	fclose(in_file);
	free(producto);
	return(0);
}


/* Implementation of functions. */

/*Menu*/
void menu(char *option) {
  puts("Menú de opciones");
  printf("\t%s\n", "(a) Guardar datos de archivo");
  printf("\t%s\n", "(b) Ver lista de productos");
  printf("\t%s\n", "(q) Salir del programa");
  puts("Seleccione una opción:");

  setbuf(stdin, NULL);
  scanf("\n%c", option);
}

/*Abre el archivo*/
FILE *openFile(char *fileName, char *mode) {
  FILE *file;

  file = fopen(fileName, mode);

  // Validar si el archivo fue abierto
  if (!file) {
    printf("Error al abrir el archivo: %s\n", fileName);
    exit(1);
  }
  return file;
}


/*Optine la informacion del archivo*/
struct product *getData(FILE *in_file){
	struct product *producto = NULL;
	char line[MAX];

	  // Leer la primer linea del archivo y no realizar ninguna operación con ella
	  fgets(line, MAX, in_file);
	  // Mientras se leen las lineas, se incrementa la memoria dinamica y se guardan los datos
	  while (fgets(line, MAX, in_file)!=NULL) {
		producto = increaseProduct(producto);
		lineProcess(line, (producto + count - 1));
	  }
	  return producto;
}

/*Incrementa en 1 el tamaño del arreglo de la estructura*/
struct product *increaseProduct(struct product *producto){
  count++;
  producto = (struct product *)realloc(producto, sizeof(struct product) * count);
  if (producto == NULL) {
    puts("Error al incrementar la memoria.");
    exit(1);
	}
}

/*Lee la linea y la guarda en la estructura*/
void lineProcess(char *line, struct product *producto){
  char *pch;
  char sep[] = ";";

  pch = strtok(line, sep);
  strcpy(producto->name, pch);

  pch = strtok(NULL, sep);
  producto->stock = atoi(pch);

  pch = strtok (NULL, sep);
  producto->price = atoi(pch);

}

/*Agrega productos desde consola*/
struct product *addProducts(int addProduct, struct product *producto, FILE *in_file){
    producto = (struct product *) realloc(producto, sizeof(struct product) *(addProduct+count) );

    int i;
    for (i = count; i < count + addProduct; ++i){
        printf("Ingrese el nombre del producto: \n");
        setbuf(stdin, NULL);
        scanf("%s", (char *)(producto + i)->name);
        printf("Ingrese la cantidad del producto: \n");
        setbuf(stdin, NULL);
        scanf("%d", &(producto + i)->stock);
        printf("Ingrese la precio del producto: \n");
        setbuf(stdin, NULL);
        scanf("%d", &(producto + i)->price);
	      fprintf(in_file, "\n%s;%d;%d", (producto+i)->name, (producto+i)->stock, (producto+i)->price);

    }
    count += addProduct;
    return producto;
}

void print(struct product *producto){
	char *search[MAX_CHARS_NAME];
	int result;

	puts("Digite una cadena de caracteres: ");
    setbuf(stdin, NULL);
    scanf("%s", (char *)search);
    result = strcmp((char *)search,"all");
    if(result==0){
    	printDataAll(producto);
    }else{
    	printData(producto,  (char *)search);
    }
}


/*Imprime toda la informacion cuando el usuario escribe all*/
void printDataAll(struct product *producto){
	printf("|%-30s|%-20s|%-20s| \n", "Nombre", "Cantidad", "Precio");
  	int total = 0;
	int i;
	for(i =0 ; i<count; i++){
		printf("|%-30s|%-20d|%-20d|\n", producto->name, producto->stock, producto->price);
		total= total + (producto->price*producto->stock);
		producto++;
	}
	printf("%-53s--------------------\n", " " );
	printf("|%-51s|%-20d|\n", "Total", total);
	return;
}


/*Imprime la informacion que coincide con lo ingredado por el usuario*/
void printData(struct product *producto, char search[MAX_CHARS_NAME]){
	int i; 
	char *pch;
  	int total = 0;
	printf("|%-30s|%-20s|%-20s| \n", "Nombre", "Cantidad", "Precio");
	for(i =0 ; i<count; i++){
		pch = strstr((char *)producto->name, (char *)search);
		if(pch != NULL){
			printf("|%-30s|%-20d|%-20d|\n", producto->name, producto->stock, producto->price);
			total= total +(producto->price*producto->stock);
		}

		
		producto++;
	}
	printf("%-53s--------------------\n", " " );
	printf("|%-51s|%-20d|\n", "Total", total);
	return;

}