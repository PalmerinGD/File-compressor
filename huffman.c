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

// Librerias
#include "huffman.h"

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
void inicializarNodos(int contador[], nodo nodos[], int total)
{
    int indiceNodo = 0;
    for(int i=0; i<256; i++)
    {
        if(contador[i] != 0)
        {
            nodos[indiceNodo].byte = i-128;
            nodos[indiceNodo].frecuencia = contador[i];
            nodos[indiceNodo].left = NULL;
            nodos[indiceNodo].right = NULL;
            indiceNodo++;
        }
    }
}

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
nodo* construirArbol(nodo nodos[], int total)
{
    nodo* arbol = NULL;
    nodo** arreglo = (nodo**) malloc(sizeof(nodo*) * total); 

    for(int i=0; i<total; i++)
    {
        arreglo[i] = &nodos[i];
    } 

    BuildMinHeap(arreglo, total);

    while(total != 1)
    {
        nodo* ntemp = (nodo*) malloc(sizeof(nodo));
        ntemp->left = ExtractMin(arreglo, &total);
        ntemp->right = ExtractMin(arreglo, &total);
        ntemp->frecuencia = (ntemp->left->frecuencia) + (ntemp->right->frecuencia);
        ntemp->byte = 5;
        InsertNodo(arreglo, ntemp, &total);
    }

    arbol = arreglo[0];
    free(arreglo);
    return arbol;
}

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
void recorridoArbol(nodo* A, char c[], int i, int* ind, valor* tabla)
{
    if(A == NULL)
        return;
    if(A->left == NULL && A->right == NULL)
    {
        tabla[*ind].c = A->byte;
        tabla[*ind].tam = i;
        tabla[*ind].frecuencia = A->frecuencia;
        memset(tabla[*ind].representacion, 0, 16);
        for(int j = 0; j<i; j++)
            tabla[*ind].representacion[j] = c[j];
        (*ind)++;
    } 
    recorridoArbol(A->left, c, i+1, ind, tabla);
    c[i] = 1;
    recorridoArbol(A->right, c, i+1, ind, tabla);
    c[i] = 0;
}

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
void llenarTabla(valor* tabla, nodo* A)
{
    char c[MAX_TAM];
    memset(c, 0, MAX_TAM);
    int indice = 0;
    recorridoArbol(A, c, 0, &indice, tabla);
}

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
void imprimirTabla(FILE* archivo, valor* tabla, int total)
{
    for(int i=0; i<total; i++)
    {
        fprintf(archivo, "%d %d ", tabla[i].c, tabla[i].frecuencia);
        for(size_t j = 0; j<tabla[i].tam; j++)
            fprintf(archivo, "%d", tabla[i].representacion[j]);
        fprintf(archivo, "\n");
    }
}

/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
int totalBits(valor *tabla, int total)
{
    int temp = 0;
    for(int i=0; i<total; i++)
    {
        temp += tabla[i].tam * tabla[i].frecuencia; 
    }
    return temp;
}


/*
void x()
Descripcion:
Recibe:
Devuelve:
Observaciones:
*/
void borrarArbol(nodo* A)
{
    if(A == NULL)
        return;
    borrarArbol(A->left);
    borrarArbol(A->right);
    free(A);
}