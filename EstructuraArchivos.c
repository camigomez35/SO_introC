#include <stdio.h>
#include <stdlib.h>

const char FILE_NAME[] = "archivo.txt";
struct product {
	char name[20];
	int stock;
	int price;
 };
void getData(FILE *in_file, struct product *ptrProduct);
void printData(struct product *producto);

int main(){
	FILE *in_file;
	struct product *producto;	

	in_file = fopen(FILE_NAME, "r");

	producto = malloc(sizeof(struct product) * 2);
	getData(in_file, producto);


	printData(producto);

	fclose(in_file);
	return(0);
}

void getData(FILE *in_file, struct product *ptrProduct){
	int i;

	if(in_file==NULL){
		printf("No se puede abrir el archivo %s\n", FILE_NAME);
		exit(8);
	}

	for(i =0 ; i<2; i++){
		fscanf(in_file, "%s", ptrProduct->name);
		fscanf(in_file, "%d", &ptrProduct->stock);
		fscanf(in_file, "%d", &ptrProduct->price);

		ptrProduct++;
	}

}

void printData(struct product *producto){
	printf("%-20s|%-20s|%-20s \n", "Nombre", "Cantidad", "Precio");
	int i;
	for(i =0 ; i<2; i++){
		printf("%-20s |", producto->name);
		printf("%-20d |", producto->stock);
		printf("%-20d\n", producto->price);
		producto++;
	}
}