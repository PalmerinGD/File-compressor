/*
Autor: Backyardigans
Profesor: Edgardo Adrián Franco Martínez
Practica03: Codificacion voraz de Huffman
Fecha: 01/Noviembre/2021
Descripcion: 

    - El algoritmo de Huffman es un algoritmo para la construccion
    de codigos de Huffman, desarrollado por David A. Huffman en
    1952.

    - Este algoritmo toma un alfabeto de "n simbolos", junto con
    sus frecuencias de aparicion asociadas y produce un codigo
    de Huffman para este alfabeto y esas frecuencias

Funcionamiento:
    Codificacion del codigo de Huffman
    1. Se crean varios arboles, uno por cada uno de los simbolos
    del alfabeto, consistiendo cada uno de los arboles en un nodo
    sin hijos, y etiquetando cada uno con su simbolo asociado
    y su frecuencia de aparicion.

    2. Se toman los dos arboles de menor frecuencia, y se unen 
    creando un nuevo arbol. La etiqueta de la raiz sera la suma
    de las frecuencias de las raices de los dos arboles que se 
    unen, y cada uno de estos arboles sera un hijo del nuevo
    arbol. Tambien se etiquetan las dos ramas del nuevo arbol:
    con un 0 la de la izquierda, y con un 1 la de la derecha.

    3. Se repite el paso 2 hasta que solo quede un arbol.
*/
//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "huffman.h"
#include "tiempo.h"


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

    printf("\n=========Codificacion de Huffman=========\n");
    printf("\n\tArchivo: %s\n", args[1]);

    double utime0, stime0, wtime0,utime1, stime1, wtime1; 

    uswtime(&utime0, &stime0, &wtime0);
    fseek(archivo, 0, SEEK_END); // Coloca el puntero al final del archivo
    size_t tam_archivo = ftell(archivo); // Indica la posicion actual del archivo 
    fseek(archivo, 0, SEEK_SET); // Coloca el puntero al inicio del archivo

    printf("\n\tTamanio del archivo: %d bits\n", tam_archivo);

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

    printf("\n\tTotal de nodos: %d\n", total_nodos);

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

    FILE* valores;
    valores = fopen("frecuencia.txt", "wb");
    size_t totalb = totalBits(tabla, total_nodos);
    fprintf(valores, "Total de bits: %d\n", totalb);
    fprintf(valores, "Total de nodos: %d\n", total_nodos);
    fprintf(valores, "Tamanio original del archivo: %d\n", tam_archivo);
    imprimirTabla(valores, tabla, total_nodos); 
    fclose(valores);

    printf("\n\tTamanio del archivo comprimido:\n");
    printf("\t\t%d bits\n", totalb);
    totalb = (size_t) ceil((float)totalb / 8);
    printf("\t\t%d bytes\n", totalb);


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
    compresion = fopen("codificacion.dat", "wb");
    fwrite(nuevoDocumento, 1, totalb, compresion);
    fclose(compresion);

    borrarArbol(arbol);

    uswtime(&utime1, &stime1, &wtime1);

    printf("\n\tTiempos:\n");
	printf("\n\treal (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("\n\tuser (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("\n\tsys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("\n\tCPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

    printf("\n=====Archivo comprimido exitosamente=====\n");
    return 0;
}