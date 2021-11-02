#include "heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct valor
{
    char c;
    int frecuencia;
    size_t tam;
    char representacion[16];
}valor;

void inicializarNodos(int contador[], nodo nodos[], int total);
nodo* construirArbol(nodo nodos[], int total);
void recorridoArbol(nodo* A, char c[], int i, int* ind, valor* tabla);
void llenarTabla(valor* tabla, nodo* A);
void imprimirTabla(FILE* archivo, valor* tabla, int total);
size_t totalBytes(valor* tabla, int total);