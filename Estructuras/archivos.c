#include <stdio.h>
#include <stdlib.h>

const char FILE_NAME[] = "input.txt";

int main(){

	int count = 0;
	FILE *in_file;
	int ch;

	in_file = fopen(FILE_NAME, "r+");

	if(in_file==NULL){
		printf("No se puede abrir el archivo %s\n", FILE_NAME);
		exit(8);
	}

	while(1){
		ch = fgetc(in_file);
		printf("%c\n", ch);
		if (ch == EOF){
			break;
		}
		++count;
	}
	
	fputc('x', in_file);
	printf("Numero de caracteres en el carchivo %s: %d\n", FILE_NAME, count);

	fclose(in_file);
	return(0);
}