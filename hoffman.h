#include "heap.h"
typedef struct valor
{
    char c;
    size_t tam;
    char representacion[8];
}valor;

void generarTabla(nodo** A, char c[], int i, int* ind, valor* tabla);