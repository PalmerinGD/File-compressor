#include <stdlib.h>
#include <stdio.h>
#include "hoffman.h"

int main()
{

    FILE *archivo;
    archivo = fopen("valores.txt", "r");
    if(archivo == NULL) exit(1);

    int total_bits;
    int total_nodos;
    int total_archivo;

    fscanf(archivo, "%d\n", &total_bits);
    fscanf(archivo, "%d\n", &total_nodos);
    fscanf(archivo, "%d\n", &total_archivo);

    nodo* nodos = malloc(sizeof(nodo)*total_nodos);
    if(nodos == NULL) exit(1);

    printf("Total bits: %d\nTotal nodos: %d\n", total_bits, total_nodos);
    int i = 0;
    while(1)
    {
        if(feof(archivo)) break;
        char inp[100];
        fgets(inp, 100, archivo);
        sscanf(inp, "%d %d", &nodos[i].byte, &nodos[i].frecuencia);
        i++;
    }

    nodo* arbol = construirArbol(nodos, total_nodos);

    FILE *comprimido;
    comprimido = fopen("comp.bn", "rb");
    if(comprimido == NULL) exit(1);

    size_t tam_archivo;
    fseek(comprimido, 0, SEEK_END);
    tam_archivo = ftell(comprimido);
    fseek(comprimido, 0, SEEK_SET);

    void* buffer = malloc(tam_archivo);
    if(buffer == NULL) exit(1);

    memset(buffer, 0, tam_archivo);
    fread(buffer, 1, tam_archivo, comprimido);

    int bit = 0;
    void* nuevo = malloc(total_archivo);
    int j = 0;
    char flag = 0;
    for(int i=0; i<total_archivo; i++)
    {
        nodo* temp = arbol;
        while(temp->left != NULL && temp->right != NULL)
        {
            if((((char*)buffer)[bit/8] & (1 << bit % 8)) != 0)
                temp = temp->right;
            else
                temp = temp->left;
            bit++;
        }
        ((char*)nuevo)[j] = temp->byte;
        j++;
    }
    FILE *nuevoArchivo;
    nuevoArchivo = fopen("copia.jpg", "wb");
    fwrite(nuevo, 1, total_archivo, nuevoArchivo);




}