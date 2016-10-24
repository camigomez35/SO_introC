/*
 ============================================================================
 Nombre      : bankers_algorithm.c
 Description : Program to check if a system is in safe state 
 Compilacion : gcc -Wall bankers_algorithm.c -o bankers
 Ejecutar    : ./bankers
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define NAME_MAX "Max.txt"
#define NAME_ALLOC "Allocation.txt"
#define NAME_AVAIL "Available.txt"

//Declaración de funciones
void printInitData();
void initData();
FILE *openFile(char *fileName, char *mode);
void read(FILE *fileMax, FILE *fileAlloc, FILE *fileAvail);
void read(FILE *arc1, FILE *arc2, FILE *arc3);
int countlines(char *FILE_NAME);

//Metodo para el hilo
void *hilo(void *atributo);


//Inicializando los valores iniciales

/*
int p = 5;      //Número de procesos
int r = 3;      //Número de recursos
int Max[10][10] = { { 7, 5, 3},
                    { 3, 2, 2},
                    { 7, 0, 2},
                    { 2, 2, 2},
                    { 4, 3, 3}};

int alloc[10][10] = { { 0, 2, 0 },
                      { 3, 0, 2 }, 
                      { 3, 0, 2 },
                      { 2, 1, 1 },
                      { 0, 0, 2 }};

int avail[10] = { 2, 2, 0 };
int need[10][10], finish[10];
*/
int p, r;
int Max[10][10];
int alloc[10][10];
int avail[10];
int need[10][10], finish[10];

int main(int argc, char* argv[]){   
    int i, j;
    int process, count, find; 
    int *exec;
    pthread_t *tids;
    int valorI[p];
    
    FILE *fileMax, *fileAlloc, *fileAvail;
    
    fileMax = openFile(NAME_MAX, "r");
    fileAlloc = openFile(NAME_ALLOC, "r");
    fileAvail = openFile(NAME_AVAIL, "r");
    
    read(fileMax, fileAlloc, fileAvail);
    
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
                    printf("\nProcess%d finished\n", i);
                    finish[i] = 1;
                    count--;
                    find = 1;

                    for (j = 0; j < r; j++) 
                    {
                        avail[j] += alloc[i][j];
                    }

                    break;
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

void read(FILE *fileMax, FILE *fileAlloc, FILE *fileAvail){
    int i ;
    int pMax, rMax, pAlloc, rAlloc;
    char lineMax[10], lineAlloc[10];
    char *pch;
    int recursos;
    
    
    
    fgets(lineMax, 10, fileMax);
    pMax = atoi(lineMax);
    fgets(lineMax, 10, fileMax);
    rMax = atoi(lineMax);
    
    fgets(lineAlloc, 10, fileAlloc);
    pAlloc = atoi(lineAlloc);
    fgets(lineAlloc, 10, fileAlloc);
    rAlloc = atoi(lineAlloc);
    
    
    
    
    if(pMax != pAlloc || rMax != rAlloc){
        printf("Por favor revise sus archivos, la cantidad de procesos y recursos deben ser iguales\n");
        exit(1);
    }
    
    p = pAlloc;
    r = rAlloc;
    
    //Para 
    
    /*
    for(i = 0; i <pMax; i++){
        fscanf(fileMax, "%d %d %d", &Max[i][0], &Max[i][1], &Max[i][2]);
    }
    */
    
    i = 0;
    while (fgets(lineMax, 10, fileMax) && i<p) {
        recursos = 0;
        pch = strtok(lineMax," ");
        while (pch != NULL && recursos<r)
        {
            Max[i][recursos] = atoi(pch);
            recursos++;
            pch = strtok(NULL, " ");
        }
        i++;
        
    }
    
    /*
    for(i = 0; i <pAlloc; i++){
        fscanf(fileAlloc, "%d %d %d", &alloc[i][0], &alloc[i][1], &alloc[i][2]);
    }
    
    */
    
    i = 0;
    while (fgets(lineAlloc, 10, fileAlloc) && i<p) {
        recursos = 0;
        pch = strtok(lineAlloc," ");
        while (pch != NULL && recursos<r)
        {
            alloc[i][recursos] = atoi(pch);
            recursos++;
            pch = strtok(NULL, " ");
        }
        i++;
    }
    
    fscanf(fileAvail, "%d %d %d", &avail[0], &avail[1], &avail[2]);
    return;
}
