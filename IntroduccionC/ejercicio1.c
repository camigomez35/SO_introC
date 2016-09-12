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
struct student{
    char name[40];
    int numStudent;
    float grade;
} student1;
 
 int main(int argc, char *argv[]){
    struct student *ptrStudent;
    ptrStudent = &student1;
    char nombre[40] = "Camila";
    ptrStudent->name[0] = *nombre;
    ptrStudent->numStudent = 1152454724;
    ptrStudent->grade = 8;
    
    printf("Name: %s \nNumbre Student: %d \nGrade: \f", ptrStudent->name, ptrStudent->numStudent, ptrStudent->grade);
    
 }