#include <stdio.h>
#include <stdlib.h>

const char FILE_NAME[] = "archivo.txt";
struct product {
	char name[20];
	int stock;
	int price;
 };


FILE *openFile(char *mode);
int countlines();
struct product *getData(FILE *in_file, struct product *ptrProduct, int numLines);
void printData(struct product *producto, int numLines);

int main(){
	struct product *producto =NULL;
	FILE *in_file;
	int numLines;
	
	in_file = openFile("r");
	
	numLines = countlines();
	numLines = numLines/3;

	producto = getData(in_file, producto, numLines);


	printData(producto, numLines);

	fclose(in_file);
	free(producto);
	return(0);
}

FILE *openFile(char *mode) {
  FILE *file;

  file = fopen(FILE_NAME, mode);

  // Validar si el archivo fue abierto
  if (!file) {
    printf("Error al abrir el archivo: %s\n", FILE_NAME);
    exit(1);
  }

  return file;
}


int countlines(){
	int ch=0;
	int lines=1;
	FILE *in_file;
	in_file = fopen(FILE_NAME, "r");
	
	while ((ch = fgetc(in_file)) != EOF){
    	if (ch == '\n'){
    		lines++;
    	}
    	
    }
    fclose(in_file);
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

void printData(struct product *producto, int numLines){
	printf("%-20s|%-20s|%-20s \n", "Nombre", "Cantidad", "Precio");
	int i;
	for(i =0 ; i<numLines; i++){
		printf("%-20s|%-20d|%-20d\n", producto->name, producto->stock, producto->price);
		producto++;
	}
	return;
}