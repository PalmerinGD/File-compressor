#include "hoffman.h"
#include <math.h>


void inicializarNodos(int contador[], nodo nodos[], int total)
{
    int indiceNodo = 0;
    for(int i=0; i<256; i++)
    {
        if(contador[i] != 0)
        {
            nodos[indiceNodo].byte = i-128;
            nodos[indiceNodo].frecuencia = contador[i];
            nodos[indiceNodo].left = NULL;
            nodos[indiceNodo].right = NULL;
            indiceNodo++;
        }
    }
}

nodo* construirArbol(nodo nodos[], int total)
{
    nodo* arbol = NULL;
    nodo** arreglo = (nodo**) malloc(sizeof(nodo*) * total); 

    for(int i=0; i<total; i++)
    {
        arreglo[i] = &nodos[i];
    } 

    BuildMinHeap(arreglo, total);

    while(total != 1)
    {
        nodo* ntemp = (nodo*) malloc(sizeof(nodo));
        ntemp->left = ExtractMin(arreglo, &total);
        ntemp->right = ExtractMin(arreglo, &total);
        ntemp->frecuencia = (ntemp->left->frecuencia) + (ntemp->right->frecuencia);
        ntemp->byte = 5;
        InsertNodo(arreglo, ntemp, &total);
    }

    arbol = arreglo[0];
    free(arreglo);
    return arbol;
}

void recorridoArbol(nodo* A, char c[], int i, int* ind, valor* tabla)
{
    if(A == 0)
        return;
    if(A->left == NULL && A->right == NULL)
    {
        tabla[*ind].c = A->byte;
        tabla[*ind].tam = i;
        tabla[*ind].frecuencia = A->frecuencia;
        memset(tabla[*ind].representacion, 0, 8);
        for(int j = 0; j<i; j++)
            tabla[*ind].representacion[j] = c[j];
        (*ind)++;
    } 
    recorridoArbol(A->left, c, i+1, ind, tabla);
    c[i] = 1;
    recorridoArbol(A->right, c, i+1, ind, tabla);
    c[i] = 0;
}

void llenarTabla(valor* tabla, nodo* A)
{
    char c[8];
    memset(c, 0, 8);
    int indice = 0;
    recorridoArbol(A, c, 0, &indice, tabla);
}

void imprimirTabla(FILE* archivo, valor* tabla, int total)
{
    for(int i=0; i<total; i++)
    {
        fprintf(archivo, "%d, %d = ", tabla[i].c, tabla[i].tam);
        for(size_t j = 0; j<tabla[i].tam; j++)
            fprintf(archivo, "%d", tabla[i].representacion[j]);
        fprintf(archivo, "\n");
    }
}

size_t totalBytes(valor *tabla, int total)
{
    float temp = 0;
    for(int i=0; i<total; i++)
    {
        temp += tabla[i].tam * tabla[i].frecuencia; 
    }
    return (size_t)ceil(temp / 8);
}
