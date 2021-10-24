#include "heap.h"
int parent(int i)
{
    if(i % 2 == 0)
        return (i/2) - 1;
    return (i/2);
}

int right(int i)
{
    return (2*i) + 2;
}

int left(int i)
{
    return (2*i) + 1;
}

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

void BuildMinHeap(nodo* A[], int total)
{
    for(int i=(total/2)-1; i>=0; i--)
    {
        MinHeapify(A, total, i);
    }
}

nodo* ExtractMin(nodo* A[], int* total)
{
    nodo* temp = A[0];
    A[0] = A[(*total)-1];
    (*total)--;
    MinHeapify(A, *total, 0);
    return temp;
}

void DecreaseKey(nodo* A[], int i)
{
    while(i > 0 && A[parent(i)]->frecuencia > A[i]->frecuencia)
    {
        nodo* temp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = temp;
        i = parent(i);
    }
}

void InsertNodo(nodo* A[], nodo* nuevo, int* total)
{
    A[*total] = nuevo; 
    (*total)++;
    DecreaseKey(A, (*total)-1);
}