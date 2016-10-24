/*
 ============================================================================
 Nombre      : bankers_algorithm.c
 Description : Program to check if a system is in safe state 
 Compilacion : gcc -Wall bankers_algorithm.c -o bankers
 Ejecutar    : ./bankers
 Evalucación4: Maria Camila Gómez Restrepo
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MAX_PROCESOS 20
#define MAX_RECURSOS 10

//Declaración de funciones
void printInitData();
void initData();
FILE *openFile(char *fileName, char *mode);
void readMatriz(FILE *file, int matriz[MAX_PROCESOS][MAX_RECURSOS], int pym[2]);
void readAvail(FILE *fileAvail);
int countlines(char *FILE_NAME);

//Metodo para el 
void *hilo(void *atributo);


//Inicializando los valores iniciales


int p, r;
int Max[MAX_PROCESOS][MAX_RECURSOS];
int alloc[MAX_PROCESOS][MAX_RECURSOS];
int avail[MAX_RECURSOS];
int need[MAX_PROCESOS][MAX_RECURSOS], finish[MAX_PROCESOS];

int main(int argc, char* argv[]){   
    int i, j;
    int process, count, find; 
    int *exec;
    pthread_t *tids;
    int valorI[p];
    int pymMax[2];
    int pymAlloc[2];

    
    if (argc != 4) {
        puts("Error al ejecutar, debes hacerlo de la siguiente forma");
        printf("%s <archivo Max> <archivo Allocation> <archivo Avail>\n", argv[0]);
        return 1;
    }

    FILE *fileMax, *fileAlloc, *fileAvail;
    
    fileMax = openFile(argv[1], "r");
    fileAlloc = openFile(argv[2], "r");
    fileAvail = openFile(argv[3], "r");
    
    readMatriz(fileMax, Max, pymMax);
    readMatriz(fileAlloc, alloc, pymAlloc);
    
    if(pymMax[0] == pymAlloc[0] && pymMax[1] == pymAlloc[1]){
        p = pymMax[0];
        r = pymMax[1];
    }else{
        printf("||%5sPor favor revise los Max y Allocation a leer ya que los procesos y recursos de ambas matrices deben ser iguales%5s||\n", "", "");
        fclose(fileMax);
        fclose(fileAlloc);
        fclose(fileAvail);
        exit(1);
    }
    readAvail(fileAvail);


    count = p;
    find = 1;

    initData();
    printInitData();

    tids = malloc(sizeof(pthread_t) * count);
    
    
    //Main procedure goes below to check for unsafe state.
    while (count >= 0 && find == 1) {
        find = 0;
        for (i = 0; i < p; i++) 
        {
            if (finish[i] == 0) 
            {
                valorI[i]=i;
                pthread_create(tids+i, NULL, hilo, (void *)&valorI[i]);
            }
        }
        
        for (i = 0; i < p; i++) 
        {
            if (finish[i] == 0) 
            {
                pthread_join(*(tids+i), (void **)&exec);
                
                if (*exec == 1) 
                {
                    printf("\nProcess %d finished\n", i);
                    finish[i] = 1;
                    count--;
                    find = 1;

                    for (j = 0; j < r; j++) 
                    {
                        avail[j] += alloc[i][j];
                    }
                }
                free(exec);
            }
            
        }
        if (find) {
            printf("Available vector:");

            for (i = 0; i < r; i++) {
                printf(" %d", avail[i]);
            }
            printf("\n");

        }else{          //No se encontró ningun i que cumpla con el criterio need < avail(i)
            if(count>0)     
                printf("\nThe processes are in unsafe state.\n");
            else
                printf("\nThe processes are in safe state.\n");
            break;
        }
    }
    
    free(tids);
    fclose(fileMax);
    fclose(fileAlloc);
    fclose(fileAvail);
}

void initData(){
    int i,j;
    //Inicializando la matriz need y el vector finish
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < r; j++)
        {
            need[i][j] = Max[i][j] - alloc[i][j];
        }
        finish[i] = 0;
    }

}

//Imprimiendo los valores iniciales
void printInitData(){
   int i,j;


    printf("\n MAX\t\tAlloc\t\tNeed\t\tAvail\n");
    for(i = 0; i < p; i++)
    {
        for( j = 0; j < r; j++){
            printf("%d ", Max[i][j]);
        }
        
        printf("\t\t");
        for( j = 0; j < r; j++){
            printf("%d ", alloc[i][j]);
        }
        
        printf("\t\t");
        for( j = 0; j < r; j++){
            printf("%d ", need[i][j]);
        }

        if(i == 0){
            printf("\t\t");
            for( j = 0; j < r; j++)
            {
                printf("%d ", avail[j]);
            }
        }
        printf("\n");
    }
}


//EL metodo del hilo :)

void *hilo(void *param){
    int *parametro = (int *)param;
    int i = *parametro;
    int *retorno = (void *)malloc(sizeof(int));
    int j;
    
    *retorno = 1;
    
    for (j = 0; j < r; j++) 
    {
        if (need[i][j] > avail[j]) 
        {
            //exec = 0;
            *retorno = 0;
            break;
            
        }
    }
    pthread_exit(retorno);
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

void readMatriz(FILE *file, int matriz[MAX_PROCESOS][MAX_RECURSOS], int pym[2]){
    int i;
    int pM, rM;
    char line[MAX_PROCESOS];
    char *pch;
    int recursos;
    
    //Lee numero de recursos y procesos
    fgets(line, MAX_PROCESOS, file);
    pym[0] = atoi(line);
    fgets(line, MAX_PROCESOS, file);
    pym[1] = atoi(line);


    i = 0;
    while (fgets(line, MAX_PROCESOS, file) && i<pym[0]) {
        recursos = 0;
        pch = strtok(line," ");
        while (pch != NULL && recursos<pym[1])
        {
            matriz[i][recursos] = atoi(pch);
            recursos++;
            pch = strtok(NULL, " ");
        }
        i++;
        
    }

    return;
}

void readAvail(FILE *fileAvail){
    char line[MAX_PROCESOS];
    int recursos;
    char *pch;

    recursos = 0;
    fgets(line, MAX_PROCESOS, fileAvail);
    pch = strtok(line," ");
    while (pch != NULL && recursos<r)
    {
        avail[recursos] = atoi(pch);
        recursos++;
        pch = strtok(NULL, " ");
    }
    return;
}
