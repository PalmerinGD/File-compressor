#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* archivo;
    archivo = fopen("C:\\Users\\morfo\\Downloads\\1.jpg", "rb");

    fseek(archivo, 0, SEEK_END); // Coloca el puntero al final del archivo
    size_t tam_archivo = ftell(archivo); // Indica la posicion actual del archivo 
    fseek(archivo, 0, SEEK_SET); // Coloca el puntero al inicio del archivo

    void* buffer = malloc(tam_archivo);
    memset(buffer, 0, tam_archivo); // Inicializa el buffer byte a byte
    /*
    for(size_t i=0; i<tam_archivo; i++)
    {
        ((char*)buffer)[i] = 0;
    } 
    
    */
    fread(buffer, 1, tam_archivo, archivo); // Lee todo el archivo y lo coloca dentro del buffer
    /*
    for(size_t i = 0; i<tam_archivo; i++)
    {
        ((char*)buffer)[i] = fgetc(archivo);
    }
    */

    fclose(archivo);

    /*
    FILE* copia;
    copia = fopen("C:\\Users\\morfo\\Downloads\\copia1.jpg", "wb");
    fwrite(buffer, 1, tam_archivo, copia);
    fclose(copia);
    */

   int temp = 0;
   int contador[256];
   memset(contador, 0, 256*sizeof(int));
   for(size_t i=0; i<tam_archivo; i++)
   {
       int valor = ((char*)buffer)[i] + 128;
       if(valor <0 || valor>256)
       {
           printf("%d\n", valor);
           continue;
       } 
       contador[valor]++;
       temp++;
   }

   int temp2 = 0;
   for(int i=0; i<256; i++)
   {
       printf("%d = %d\n", i, contador[i]);
       temp2 += contador[i];
   }


   printf("Temp:  %d\n", temp);
   printf("Temp2: %d", temp2);











}