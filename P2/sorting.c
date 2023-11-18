/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stddef.h>
#include <stdlib.h>

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/

int SelectSort(int* array, int ip, int iu)
{
  if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

  int aux = 0, i = 0, ob = 0, imin = 0;

  for(i = ip; i < iu; i++) {
    imin = min(array, i, iu);

    if(i != imin){
      aux = array[i];
      array[i] = array[imin];
      array[imin] = aux;
    }
    ob+=iu-i;
  }

  return ob;
}


int SelectSortInv(int* array, int ip, int iu)
{
  if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

  int aux = 0, i = 0, ob = 0, imin = 0;

  for(i = iu; i > ip; i--) {
    imin = min(array, ip, i);

    if(i != imin){
      aux = array[i];
      array[i] = array[imin];
      array[imin] = aux;
    }
    ob+=iu-i;
  }

  return ob;
}

int min(int* array, int ip, int iu)
{
  if(!array || ip < 0 || iu < 0 || ip > iu) return ERR;

  int i = 0, min = ip;

  for(i = ip + 1; i <= iu; i++) {
    if(array[i] < array[min]) min = i;
  }

  return min;
}

/**Práctica 2*/

int mergesort(int* tabla, int ip, int iu) 
{
  if(!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  if(ip == iu) return 0;

  int imedio = (ip + iu) / 2;
  int ob1 = mergesort(tabla, ip, imedio);
  if (ob1 == ERR) return ERR;
  int ob2 = mergesort(tabla, imedio + 1, iu);
  if (ob2 == ERR) return ERR;
  int ob3 = merge(tabla, ip, iu, imedio);
  if (ob3 == ERR) return ERR;
  

  return ob1 + ob2 + ob3;
}


int merge(int* tabla, int ip, int iu, int imedio)
{
  if(!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  int* aux = NULL;
  int i = ip, j = imedio + 1, k = 0, ob = 0;

  aux = (int*)malloc(sizeof(int) * (iu - ip + 1));
  if(!aux) return ERR;

  while(i <= imedio && j <= iu) {
    if(tabla[i] < tabla[j]) {
      aux[k] = tabla[i];
      i++;
    }
    else {
      aux[k] = tabla[j];
      j++;
    }
    ob++;
    k++;
  }

  if(i > imedio) {
    while(j <= iu) {
      aux[k] = tabla[j];
      j++;
      k++;
    }
  }
  else {
    while(i <= imedio) {
      aux[k] = tabla[i];
      i++;
      k++;
    }
  }

  for(i = ip, k = 0; i <= iu; i++, k++) {
    tabla[i] = aux[k];
  }

  free(aux);

  return ob;
}


int partition(int* tabla, int ip, int iu, int* pos) {
    if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

    int pivot = tabla[ip];
    int i = ip + 1;

    for (int j = ip + 1; j <= iu; j++) {
        if (tabla[j] < pivot) {
            // Intercambiar elementos
            int temp = tabla[j];
            tabla[j] = tabla[i];
            tabla[i] = temp;
            i++;
        }
    }

    // Colocar el pivote en su posición final
    tabla[ip] = tabla[i - 1];
    tabla[i - 1] = pivot;

    *pos = i - 1;  // Posición final del pivote
    return iu - ip;  // Número de operaciones básicas
}

int median(int* tabla, int ip, int iu, int* pos) {
    if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

    *pos = ip;
    return 0;
}

int quicksort(int* tabla, int ip, int iu) {
    if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

    if (ip < iu) {
        int pos;
        int ob = median(tabla, ip, iu, &pos);
        if (ob == ERR) return ERR;

        // Intercambiar el pivote con el primer elemento
        int temp = tabla[ip];
        tabla[ip] = tabla[pos];
        tabla[pos] = temp;

        int ob_partition = partition(tabla, ip, iu, &pos);
        if (ob_partition == ERR) return ERR;

        int ob1 = quicksort(tabla, ip, pos - 1);
        int ob2 = quicksort(tabla, pos + 1, iu);

        if (ob1 == ERR || ob2 == ERR) return ERR;

        return ob + ob_partition + ob1 + ob2;
    }

    return 0;  // Caso base: ya está ordenado
}


