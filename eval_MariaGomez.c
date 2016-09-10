/*
 * Maria Camila Gómez Restrepo 
 */
 
 /*
 * Include
 */
 #include <stdio.h>
 #include <stdlib.h>
 #define MAX_CHARS_NAME 20

 /*
 * Variables Globales y Firma de metodos
 */
 int sizeActual = 0;
 char (*product)[MAX_CHARS_NAME] = NULL;
 float *stock = NULL;
 void menu(char *option);
 void addProducts( int addProduct);
 void showAllProducts(int addProduct);

 /*
 * Main
 */
 int main(int argc, char *argv[]){
  char option = ' ';
  int addProduct;
  char search[MAX_CHARS_NAME];

  do {
    menu(&option);

    switch(option) {
      case 'a':
            puts("¿Cuantos productos desea agregar?");
            setbuf(stdin, NULL);
            scanf("%d\n", &addProduct);
            addProducts(addProduct);
        break;
      case 'b':
            //puts("Digite una cadena de caracteres: ");
            //setbuf(stdin, NULL);
            //scanf("%s", search);
            showAllProducts( addProduct);
            
        break;
      case 'q':
        puts("Saliendo del programa...");
        break;
      default:
        puts("Opción no valida, intenta de nuevo.");
        break;
    }
  } while(option != 'q');


  return 0;
 }

/*
 * Implementación de metodos
 */
void menu(char *option) {
  puts("Menú de opciones");
  printf("%5s %s\n"," ", "(a) Registrar productos");
  printf("%5s %s\n"," ", "(b) Ver lista de productos");
  printf("%5s %s\n"," ", "(q) Salir del programa");
  puts("Seleccione una opción:");

  setbuf(stdin, NULL);
  scanf("\n%c", option);
}

void addProducts(int addProduct){
    product = (char (*)[MAX_CHARS_NAME]) realloc(product, sizeof(char [MAX_CHARS_NAME]) *(addProduct+sizeActual) );
    stock = (float (*)) realloc(stock, sizeof(float) * addProduct);

    int i;
    for (i = sizeActual; i < sizeActual + addProduct; ++i){
        printf("Ingrese el nombre del producto: \n");
        setbuf(stdin, NULL);
        scanf("%s", (char *)(product + i));
        printf("Ingrese la cantidad del producto: \n");
        setbuf(stdin, NULL);
        scanf("%f", (stock + i));
    }
    sizeActual = sizeActual + addProduct;
}

void showAllProducts( int addProduct){
  int i;
  printf("\n %-50s|%12s\n", "Nombre del producto", "cantidad");
  for (i = 0; i < sizeActual; i++) {
    printf("%-50s|%12.2f\n", *(product + i), *(stock + i));
  }
}