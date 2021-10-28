#include "hoffman.h"

void generarTabla(nodo** A, char c[], int i, int* ind, valor* tabla)
{
    if(*A == 0)
        return;
    if((*A)->left == NULL && (*A)->right == NULL)
    {
        tabla[*ind].c = (*A)->byte;
        tabla[*ind].tam = i;
        memset(tabla[*ind].representacion, 0, 8);
        for(int j = 0; j<i; j++)
            tabla[*ind].representacion[j] = c[j];
        (*ind)++;
    } 
    generarTabla(&((*A)->left), c, i+1, ind, tabla);
    c[i] = 1;
    generarTabla(&((*A)->right), c, i+1, ind, tabla);
    c[i] = 0;
}

void imprimirTabla(FILE* archivo, valor* tabla, int total)
{
    for(int i=0; i<total; i++)
    {
        fprintf(archivo, "%d = ", tabla[i].c + 128);
        for(size_t j = 0; j<tabla[i].tam; j++)
            fprintf(archivo, "%d", tabla[i].representacion[j]);
        fprintf(archivo, "\n");
    }
}