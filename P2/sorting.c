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

//Práctica 2

int mergesort(int* tabla, int ip, int iu) 
{
  if(!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  if(ip == iu) return 0;

  int imedio = (ip + iu) / 2;
  int ob1 = mergesort(tabla, ip, imedio);
  int ob2 = mergesort(tabla, imedio + 1, iu);
  int ob3 = merge(tabla, ip, iu, imedio);
  

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


