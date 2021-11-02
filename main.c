//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    if(buffer == NULL) exit(1);

    memset(buffer, 0, tam_archivo); // Inicializa el buffer byte a byte
    fread(buffer, 1, tam_archivo, archivo); // Lee todo el archivo y lo coloca dentro del buffer
    fclose(archivo);

    int contador[256]; //Guarda las cantidades totales de los bytes
    memset(contador, 0, 256*sizeof(int));// Inicializa contador
    for(size_t i=0; i<tam_archivo; i++)
    {
        int valor_byte = ((char*)buffer)[i] + 128;
        contador[valor_byte]++;
    }

    int total_nodos = 0;
    for(int i=0; i<256; i++)
        if(contador[i] != 0) total_nodos++;


    nodo* nodos = (nodo*)malloc(total_nodos*sizeof(nodo)); //Se almacenan la cantidad total de nodos

    valor* tabla = (valor*) malloc(total_nodos*sizeof(valor));

    if(nodos == NULL || tabla == NULL)
    {
        printf("Error al reservar memoria\n");
        exit(1);
    }

    for(int i=0; i<total_nodos; i++)
    {
        tabla[i].c = 0;
        tabla[i].frecuencia = -1;
        tabla[i].tam = 0;
        memset(tabla[i].representacion, 0, 16);
    } 
    inicializarNodos(contador, nodos, total_nodos); //Inicializa los nodos con sus respectivos bytes

    nodo* arbol = construirArbol(nodos, total_nodos); //Construye el arbol y regresa la direccion de la raiz
    llenarTabla(tabla, arbol); //Llena la tabla de valores

    char ruta[100];
    printf("Nombre del archivo: ");
    scanf("%[^\n]s", ruta);
    FILE* valores;
    valores = fopen(ruta, "wb");
    size_t totalb = totalBytes(tabla, total_nodos);
    fprintf(valores, "%d\n", totalb);
    fprintf(valores, "%d\n", total_nodos);
    fprintf(valores, "%d\n", tam_archivo);
    imprimirTabla(valores, tabla, total_nodos); 
    fclose(valores);
    totalb = (size_t) ceil((float)totalb / 8);
    void* nuevoDocumento = malloc(totalb);
    memset(nuevoDocumento, 0, totalb);

    int bit = 0;
    for(size_t i = 0; i<tam_archivo; i++)
    {
        char c = ((char*)buffer)[i];
        int j;
        for(j=0; j<total_nodos; j++)
        {
            if(c == tabla[j].c)
                break;
        }
        for(int k=0; k<tabla[j].tam; k++)
        {
            if(tabla[j].representacion[k] == 1)
                ((char*)nuevoDocumento)[bit/8] |= (1 << (bit % 8));
            else if(tabla[j].representacion[k] == 0)
                ((char*)nuevoDocumento)[bit/8] |= (0 << (bit % 8));
            bit++;
        }
    }
    FILE* compresion;
    compresion = fopen("comp.bn", "wb");
    fwrite(nuevoDocumento, 1, totalb, compresion);
    fclose(compresion);
}