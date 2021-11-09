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
    Decodificacion del codigo de Huffman
    1. A partir del arbol de codificacion, comenzar a recorrer los caminos 
    segun los bits de la codificacion. Al llegar a un nodo hoja se toma el valor de
    esta y coloca en el archivo original.

    2. Se repite el paso 1 a partir del bit siguiente de la codificacion comenzando
    un nuevo recorrido a partir de la raiz del arbol de la codificiacion.

    3. La decodificacion termina una vez se hallan recorrido todos los bits de la codificacion.
*/
//Librerias
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "tiempo.h"

int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        printf("Ingrese el nombre del nuevo archivo\n");
        exit(1);
    }

    printf("\n========Decodificacion de Huffman========\n");

    double utime0, stime0, wtime0,utime1, stime1, wtime1; 

    uswtime(&utime0, &stime0, &wtime0);
    FILE *archivo;
    archivo = fopen("frecuencia.txt", "r");
    if(archivo == NULL) exit(1);

    int total_bits; //Total de bits que va a leer
    int total_nodos; //Total de nodos que va a haber
    int total_archivo; //Total de bytes del archivo

    fscanf(archivo, "Total de bits: %d\n", &total_bits);
    fscanf(archivo, "Total de nodos: %d\n", &total_nodos);
    fscanf(archivo, "Tamanio original del archivo: %d\n", &total_archivo);

    nodo* nodos = (nodo*)malloc(sizeof(nodo)*total_nodos);
    if(nodos == NULL) exit(1);

    int i = 0;
    int contador[256]; 
    memset(contador, 0, 256*sizeof(int)); //Se inicializa el contador
    while(i < total_nodos)
    {
        char inp[100];
        fgets(inp, 100, archivo);
        int byte;
        int frecuencia;
        sscanf(inp, "%d %d", &byte, &frecuencia);
        contador[byte+128] = frecuencia;
        i++;
    }

    fclose(archivo);

    inicializarNodos(contador, nodos); //Se inicializan los nodos con el contador
    nodo* arbol = construirArbol(nodos, total_nodos); //Se construye el arbol

    FILE *comprimido;
    comprimido = fopen("codificacion.dat", "rb");
    if(comprimido == NULL) exit(1);

    size_t tam_archivo;
    fseek(comprimido, 0, SEEK_END);
    tam_archivo = ftell(comprimido);
    fseek(comprimido, 0, SEEK_SET);

    void* buffer = malloc(tam_archivo);
    if(buffer == NULL) exit(1);
    memset(buffer, 0, tam_archivo);

    fread(buffer, 1, tam_archivo, comprimido); //Se lee el archivo

    void* nuevo = malloc(total_archivo);
    memset(nuevo, 0, total_archivo);
    if(nuevo == NULL) exit(1);

    int bit = 0;
    for(int j=0; j< total_archivo; j++)
    {
        nodo* temp = arbol;
        while(temp->left != NULL && temp->right != NULL)
        {
            if((((char*)buffer)[bit/8] & (1 << (bit % 8))) != 0)
                temp = temp->right;
            else if((((char*)buffer)[bit/8] & (1 << (bit % 8))) == 0)
                temp = temp->left;
            bit++;
        }
        ((char*)nuevo)[j] = temp->byte;
    }
    FILE *nuevoArchivo;
    nuevoArchivo = fopen(argv[1], "wb");
    if(nuevoArchivo == NULL) exit(1);
    fwrite(nuevo, 1, total_archivo, nuevoArchivo);
    fclose(nuevoArchivo);

    borrarArbol(arbol);

    uswtime(&utime1, &stime1, &wtime1);

    printf("\n\tTiempos:\n");
	printf("\n\treal (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("\n\tuser (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("\n\tsys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("\n\tCPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

    printf("\n====Archivo descomprimido exitosamente===\n");
    return 0;
}