#include "heap.h"
#include <stdio.h>
#include <string.h>

typedef struct valor
{
    char c;
    size_t tam;
    char representacion[8];
}valor;

void generarTabla(nodo** A, char c[], int i, int* ind, valor* tabla);
void imprimirTabla(FILE* archivo, valor* tabla, int total);