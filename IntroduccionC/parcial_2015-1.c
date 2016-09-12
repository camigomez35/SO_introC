/*
 * Maria Camila Gómez Restrepo 
 */
 
 /*
 * Include
 */
 #include <stdio.h>
 
 /*
 * Variables Globales y Firma de metodos
 */
 double CONSTANTE = -1;
 double MAXIMO = 20;
 
 void menu(char *option);
 void ingrese_X(double *x);
 void seno(double x);
 void coseno(double x);
 double factorial(double n);
 double exponente(double base, double expo);
 
 int main(int argc, char *argv[]){
    char option = ' ';
    double x = 1;
    
    while(option != 'q'){
        menu(&option);
        
        switch(option){
            case 'a':
                printf("Ingrse el valor de x: ");
                setbuf(stdin, NULL);
                scanf("%lf", &x);
                printf("\n");
            break;
            case 'b':
                seno(x);
            break;
            case 'c':
                coseno(x);
            break;
        }
    }
    return 0;
 }

void menu(char *option){
    printf("Bienvenido al menu del parcial 1 de Sistemas Operativos \n");
    printf("(a) Ingresar X \n");
    printf("(b) Sin\n");
    printf("(c) Cos\n");
    printf("(q) Salir\n");
    printf("¿Que desea hacer?: ");
    
    setbuf(stdin, NULL);
    scanf("%c", option);
    return;
}


 void seno(double x){
     double i;
     double termino;
     double resultado = 0;
     for(i = 0; i<MAXIMO; i++){
         printf("i: %.2lf\n", i);
         termino = exponente(CONSTANTE,i);
         termino = termino*exponente(x,((i*2)+1));
         termino = termino/factorial(2*i+1);
         
         printf("Termino: %.2lf\n", termino);
         resultado = resultado + termino;
     }
     printf("Resultado de seno: %.2lf \n" , resultado);
 }
 
 void coseno(double x){
     double i;
     double termino;
     double resultado = 0;
     for(i = 0; i<MAXIMO; i++){
         printf("i: %.2lf\n", i);
         termino = exponente(CONSTANTE,i);
         termino = termino*exponente(x,(i*2));
         termino = termino/factorial(2*i);
         
         printf("Termino: %.2lf\n", termino);
         resultado = resultado + termino;
     }
     printf("Resultado coseno: %.2lf\n" , resultado);
 }
 
 double factorial(double n){
     double i;
     double aux = 1;
     for(i = 1; i<=n; i++){
         aux = aux*(i);
     }
     return aux;
 }
 
 double exponente(double base, double expo){
    double termino;
     if(expo==0){
         return 1;
     }
     termino = base*(exponente(base, expo-1));
     return termino;
 }