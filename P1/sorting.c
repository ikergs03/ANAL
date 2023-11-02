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


