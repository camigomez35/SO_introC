/*
================================================================================
Name         : Eval_Estructuras.c
Author       : Maria Camila Gomez Restrepo
Version      : 1.0
Compilation  : gcc -Wall Eval1_Estructuras.c -o Eval_Estructuras.out
Execution    : ./Eval_Estructuras.out
================================================================================
*/

/* Including headers or libraries. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARS_NAME 20


/* Definition of macros and constants. */


/* Definition of structures. */
struct product {
	char name[MAX_CHARS_NAME];
	int stock;
	int price;
 };

/* Declaring functions. */
void menu(char *option);
int countlines();
FILE *openFile(char *fileName, char *mode);
struct product *getData(FILE *in_file, struct product *ptrProduct, int numLines);
void printDataAll(struct product *producto, int numLines);
void printData(struct product *producto, int numLines, char search[MAX_CHARS_NAME]);

/* Global variables. */


/* Main function. */
int main(){
	struct product *producto =NULL;
	char *search[MAX_CHARS_NAME] ;
	int result;
	char fileName[MAX_CHARS_NAME];
	FILE *in_file;
	int numLines;
	char option = ' ';
	
	do {
    menu(&option);

    switch(option) {
      case 'a':
            puts("Diga el nombre del archivo que desea leer: ");
            setbuf(stdin, NULL);
            scanf("%s", fileName);
            in_file = openFile(fileName, "r");
            numLines = countlines(in_file);
						numLines = numLines/3;
						producto = getData(in_file, producto, numLines);
            
        break;
      case 'b':
      			puts("Digite una cadena de caracteres: ");
            setbuf(stdin, NULL);
            scanf("%s", (char *)search);
            result = strcmp((char *)search,"all");
            if(result==0){
            	printDataAll(producto, numLines);
            }else{
            	printData(producto, numLines,  (char *)search);
            }
            
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
void menu(char *option) {
  puts("Menú de opciones");
  printf("\t%s\n", "(a) Guardar datos de archivo");
  printf("\t%s\n", "(b) Ver lista de productos");
  printf("\t%s\n", "(q) Salir del programa");
  puts("Seleccione una opción:");

  setbuf(stdin, NULL);
  scanf("\n%c", option);
}

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

int countlines(FILE *in_file){
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

struct product *getData(FILE *in_file, struct product *ptrProduct, int numLines){
	int i;
	ptrProduct = malloc(sizeof(struct product) * numLines);
	
	for(i =0 ; i<numLines; i++){
		fscanf(in_file, "%s", ptrProduct->name);
		fscanf(in_file, "%d", &ptrProduct->stock);
		fscanf(in_file, "%d", &ptrProduct->price);

		ptrProduct++;
	}
	return (ptrProduct-numLines);
}

void printDataAll(struct product *producto, int numLines){
	printf("%-20s|%-20s|%-20s \n", "Nombre", "Cantidad", "Precio");
	int i;
	for(i =0 ; i<numLines; i++){
		printf("%-20s|%-20d|%-20d\n", producto->name, producto->stock, producto->price);
		producto++;
	}
	return;
}

void printData(struct product *producto, int numLines, char search[MAX_CHARS_NAME]){
	int i; 
	char *pch;
  
	printf("%-20s|%-20s|%-20s \n", "Nombre", "Cantidad", "Precio");
	for(i =0 ; i<numLines; i++){
			pch = strstr((char *)producto->name, (char *)search);
			if(pch != NULL){
				printf("%-20s|%-20d|%-20d\n", producto->name, producto->stock, producto->price);
			}
		producto++;
	}
	return;

}
