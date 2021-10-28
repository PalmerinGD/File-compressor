//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hoffman.h"


int main(int arg, char* args[])
{

    if(arg != 2)
    {
        printf("Ingrese la ruta del archivo\n");
        exit(1);
    }

    FILE* archivo;
    archivo = fopen(args[1], "rb");

    if(archivo == NULL)
    {
        printf("Error al abrir el archivo: %s \nVerifique la ruta\n", args[1]);
        exit(1);
    }

    fseek(archivo, 0, SEEK_END); // Coloca el puntero al final del archivo
    size_t tam_archivo = ftell(archivo); // Indica la posicion actual del archivo 
    fseek(archivo, 0, SEEK_SET); // Coloca el puntero al inicio del archivo

    void* buffer = malloc(tam_archivo);
    memset(buffer, 0, tam_archivo); // Inicializa el buffer byte a byte
    /*
    for(size_t i=0; i<tam_archivo; i++)
    {
        ((char*)buffer)[i] = 0;
    } 
    
    */
    fread(buffer, 1, tam_archivo, archivo); // Lee todo el archivo y lo coloca dentro del buffer
    /*
    for(size_t i = 0; i<tam_archivo; i++)
    {
        ((char*)buffer)[i] = fgetc(archivo);
    }
    */

    fclose(archivo);

    /*
    FILE* copia;
    copia = fopen("C:\\Users\\morfo\\Downloads\\copia1.jpg", "wb");
    fwrite(buffer, 1, tam_archivo, copia);
    fclose(copia);
    */

   int temp = 0;
   int contador[256];
   memset(contador, 0, 256*sizeof(int));

   for(size_t i=0; i<tam_archivo; i++)
   {
       int valor = ((char*)buffer)[i] + 128;
       /*
       if(valor <0 || valor>256)
       {
           printf("%d\n", valor);
           continue;
       } 
       */
       contador[valor]++;
       temp++;
   }
    int total_nodos = 0;
    for(int i=0; i<256; i++)
    {
        if(contador[i] != 0)
        total_nodos++;
   }

   // Se almacenan los nodos
   nodo* nodos = (nodo*)malloc(total_nodos*sizeof(nodo));
   valor* tabla = (valor*) malloc(total_nodos*sizeof(valor));
    if(nodos == NULL || tabla == NULL)
    {
        printf("Error al reservar memoria\n");
        exit(1);
    }
    int j = 0;
    for(int i=0; i<256; i++)
    {
        if(contador[i] != 0)
        {
            nodos[j].byte = i;
            nodos[j].frecuencia = contador[i];
            nodos[j].left = NULL;
            nodos[j].right = NULL;
            j++;
        }
    }
    nodo** arreglo = (nodo**) malloc(sizeof(nodo*) * total_nodos); 
    for(int i=0; i<total_nodos; i++)
    {
        arreglo[i] = &nodos[i];
    } 
    BuildMinHeap(arreglo, total_nodos);
    while(total_nodos != 1)
    {
        nodo* ntemp = (nodo*) malloc(sizeof(nodo));
        ntemp->left = ExtractMin(arreglo, &total_nodos);
        ntemp->right = ExtractMin(arreglo, &total_nodos);
        ntemp->frecuencia = (ntemp->left->frecuencia) + (ntemp->right->frecuencia);
        ntemp->byte = 5;
        InsertNodo(arreglo, ntemp, &total_nodos);
    }
    nodo* arbol = arreglo[0];
    free(arreglo);
    printf("Despues: \n");
    char c[8];
    memset(c, 0, 8);
    int indice = 0;
    generarTabla(&arbol,c, 0, &indice, tabla); 
    for(int i=0; i<indice; i++)
    {
        printf("Valor %d = ", tabla[i].c + 128);
        for(size_t j = 0; j<tabla[i].tam; j++)
            printf("%d", tabla[i].representacion[j]);
        printf("\n");
    }











}