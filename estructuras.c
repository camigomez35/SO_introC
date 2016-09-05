/*
 * Maria Camila Gómez Restrepo 
 */
 
 /*
 * Include
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
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
    
    //student1.name[0] = "Camila";
    strcpy(&student1.name[0], "Camila");
    ptrStudent->numStudent = 1152454724;
    ptrStudent->grade = 8;
    
    printf("Name: %s \nNumbre Student: %d \nGrade: %f", ptrStudent->name, ptrStudent->numStudent, ptrStudent->grade);
    
    
    return(0);
}