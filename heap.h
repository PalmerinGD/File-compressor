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
void MinHeapify(nodo* A[], int total, int i); //
void BuildMinHeap(nodo* A[], int total);
nodo* ExtractMin(nodo* A[], int* total);
void DecreaseKey(nodo* A[], int i);
void InsertNodo(nodo* A[], nodo* nuevo, int* total);