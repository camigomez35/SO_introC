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
#include <unistd.h>

/* Global variables. */


/* Main function. */
int main (int argc, char *argv[]) {
  char *puntoC;
  char *ejecutable;
  pid_t child_pid;
  char completo[100] ="./";
  int estado;

	if (argc != 3) {
	    puts("Error al ejecutar, debes hacerlo de la siguiente forma");
	    printf("%s <archivo_entrada> \n", argv[0]);
	    return 1;
	}

  puntoC = argv[1];
  ejecutable = argv[2];
  
  
  switch(child_pid=fork()) {
      case -1:
          return -1;
      case 0:
          execlp("gcc", "gcc", puntoC, "-o", ejecutable, NULL);
          exit(0);
        
      default: /* Codigo ejecutado por el padre */
          wait(&estado);
          strcat(completo, ejecutable);
  }

  switch(child_pid=fork()) {
      case -1:
          return -1;
      case 0: 

          execl(completo, ejecutable, NULL);
      default: /* Codigo ejecutado por el padre */
          wait(&estado);
  }

  return 0;
  /* Creacion del proceso hijo. */
 }