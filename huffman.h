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
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

// Librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"

#define MAX_TAM 16
// Definicion de struct tipo valor
typedef struct valor
{
    char c; //Valor del byte
    int frecuencia; //Frecuencia con la que aparece
    size_t tam; //Tamanio en bits de su nueva representacion
    char representacion[MAX_TAM]; //Representacion 
}valor;

// Defincion de funciones
void inicializarNodos(int contador[], nodo nodos[]); //Inicializa los nodos del arbol de acuerdo al contador
nodo* construirArbol(nodo nodos[], int total); // Construye el arbol de Huffman
void recorridoArbol(nodo* A, char c[], int i, int* ind, valor* tabla); // Recorre el arbol para generar las conversiones
void llenarTabla(valor* tabla, nodo* A); // LLena la tabla de valores con el arbol
void imprimirTabla(FILE* archivo, valor* tabla, int total); // Imprime la tabla de valores
int totalBits(valor* tabla, int total); // Retorna la cantidad total de bits a ocupar
void borrarArbol(nodo* A); // Borra el arbol de Huffman

#endif