/*
Autor: Backyardigans
Profesor: Edgardo Adrián Franco Martínez
Practica03: Codificacion voraz de Huffman
Fecha: 01/Noviembre/2021

Descripcion: 
Implementacion de un MinHeap para poder implementar una cola de prioridades.

Observaciones:
Construye e inserta los nodos del arbol con base a la frecuencia
*/

#ifndef __HEAP_H__
#define __HEAP_H__

// Estructura de nodo
typedef struct nodo
{
    char byte;
    int frecuencia;
    struct nodo* left;
    struct nodo* right;
} nodo;

// Definicion de funciones

int parent(int i); //Devuelve el padre del nodo
int right(int i); //Devuelve el hijo derecho
int left(int i); //Devuelve el hijo izquierdo
void MinHeapify(nodo* A[], int total, int i); //Manteniene la propiedad de un MinHeap
void BuildMinHeap(nodo* A[], int total); //Construye un MinHeap
nodo* ExtractMin(nodo* A[], int* total); //Extrae el elemento mas chico del MinHeap
void InsertNodo(nodo* A[], nodo* nuevo, int* total); //Inserta un nuevo nodo al MinHeap

#endif