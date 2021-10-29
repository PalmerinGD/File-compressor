#include "heap.h"
#include <stdio.h>
#include <string.h>

typedef struct valor
{
    char c;
    int frecuencia;
    size_t tam;
    char representacion[8];
}valor;

void generarTabla(nodo** A, char c[], int i, int* ind, valor* tabla);
void imprimirTabla(FILE* archivo, valor* tabla, int total);
long tamano(valor* tabla, int total);