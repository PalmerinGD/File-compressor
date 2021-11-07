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

//Librerias
#include "heap.h"

/*
int parent(int i)
Descripcion: Obtiene el padre del nodo en la posicion i
Recibe: int i(Posicion del nodo)
Devuelve: int(Posicion del padre)
Observaciones: No verifica que dicha posicion este fuera de rango
*/
int parent(int i)
{
    if(i % 2 == 0)
        return (i/2) - 1;
    return (i/2);
}

/*
int parent(int i)
Descripcion: Obtiene el nodo hijo derecho del nodo en la posicion i
Recibe: int i(Posicion del nodo)
Devuelve: int(Posicion del nodo hijo izquierdo)
Observaciones: No verifica que dicha posicion este fuera de rango
*/
int right(int i)
{
    return (2*i) + 2;
}

/*
int left(int i)
Descripcion: Obtiene el nodo hijo izquierdo del nodo en la posicion i
Recibe: int i(Posicion del nodo)
Devuelve: int(Posicion del nodo hijo izquierdo)
Observaciones: No verifica que dicha posicion este fuera de rango
*/
int left(int i)
{
    return (2*i) + 1;
}

/*
void MinHeapify(nodo* A[], int total, int i)
Descripcion: Mantiene la propiedad de un MinHeap
Recibe: nodo* A[](Referencia a un arreglo de punteros de tipo nodo), int total(Total de nodos en el heap),
int i(Indice del nodo para verificar)
Devuelve: void
Observaciones: Si dicho nodo no rompe con la propiedad, no modificara nada
*/
void MinHeapify(nodo* A[],int total , int i)
{
    int min;
    int l = left(i);
    int r = right(i);
    if(l < total && A[l]->frecuencia < A[i]->frecuencia)
        min = l;
    else min = i;
    if(r < total && A[r]->frecuencia < A[min]->frecuencia)
        min = r;
    if(min != i)
    {
        nodo* temp = A[i];
        A[i] = A[min];
        A[min] = temp;
        MinHeapify(A, total, min);
    }
}

/*
void BuildMinHeap(nodo* A[], int total)
Descripcion: Construye un heap de tipo nodo
Recibe: nodo* A[](Referencia a un arreglo de punteros de tipo nodo), int total(Total de nodos en el heap)
Devuelve: void
Observaciones: El arreglo debe ya tener los nodos con las frecuencias
*/
void BuildMinHeap(nodo* A[], int total)
{
    for(int i=(total/2)-1; i>=0; i--)
        MinHeapify(A, total, i);
}

/*
nodo* ExtractMin(nodo* A[], int* total)
Descripcion: Devuelve el nodo con valor mas chico del heap
Recibe: nodo* A[](Referencia a un arreglo de punteros de tipo nodo), int* total(Referencia al total de nodos en el heap)
Devuelve: nodo*(Referencia a un nodo)
Observaciones: Devuelve la referencia de un nodo y decrementa el tamano total de nodos
*/
nodo* ExtractMin(nodo* A[], int* total)
{
    nodo* temp = A[0];
    A[0] = A[(*total)-1];
    (*total)--;
    MinHeapify(A, *total, 0);
    return temp;
}

/*
void InsertNodo(nodo* A[], nodo* nuevo, int* total)
Descripcion: Inserta un nuevo nodo en el heap
Recibe: nodo* A[](Referencia a un arreglo de puntero de tipo nodo), nodo* nuevo(Referencia a un nuevo nodo),
int* total(Referencia al total de nodos en el heap)
Devuelve: void
Observaciones: El heap ya debio de haber sido construido
*/
void InsertNodo(nodo* A[], nodo* nuevo, int* total)
{
    A[*total] = nuevo; 
    (*total)++;
    int i = (*total) - 1;
    while(i > 0 && A[parent(i)]->frecuencia > A[i]->frecuencia)
    {
        nodo* temp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = temp;
        i = parent(i);
    }
}
