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
#include <stdio.h>

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/

int SelectSort(int* array, int ip, int iu)
{
  int aux = 0, i = 0, ob = 0, imin = 0;
  
  if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

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
  int aux = 0, i = 0, ob = 0, imin = 0;

  if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

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
  int i = 0, min;

  if(!array || ip < 0 || iu < 0 || ip > iu) return ERR;

  min = ip;

  for(i = ip + 1; i <= iu; i++) {
    if(array[i] < array[min]) min = i;
  }

  return min;
}

/**Práctica 2*/

int mergesort(int* tabla, int ip, int iu) 
{
  int imedio, ob1, ob2, ob3;

  if(!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  if(ip == iu) return 0;

  imedio = (ip + iu) / 2;
  ob1 = mergesort(tabla, ip, imedio);
  if (ob1 == ERR) return ERR;
  ob2 = mergesort(tabla, imedio + 1, iu);
  if (ob2 == ERR) return ERR;
  ob3 = merge(tabla, ip, iu, imedio);
  if (ob3 == ERR) return ERR;
  

  return ob1 + ob2 + ob3;
}


int merge(int* tabla, int ip, int iu, int imedio)
{
  int* aux = NULL;
  int i, j, k = 0, ob = 0; 

  if(!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  i = ip; 
  j = imedio + 1;

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
  int pivot, i, j;

  if (!tabla || ip < 0 || iu < 0 || ip > iu){
    printf("Error en los parametros de entrada partition\n");
    return ERR;
  } 

  pivot = tabla[ip];
  i = ip + 1;

  for (j = ip + 1; j <= iu; j++) {
      if (tabla[j] < pivot) {
          /* Intercambiar elementos*/
          int temp = tabla[j];
          tabla[j] = tabla[i];
          tabla[i] = temp;
          i++;
      }
  }

  /*Colocar el pivote en su posición final*/
  tabla[ip] = tabla[i - 1];
  tabla[i - 1] = pivot;

  *pos = i - 1;  /*Posición final del pivote*/
  return iu - ip;  /*Número de operaciones básicas*/
}

int median(int* tabla, int ip, int iu, int* pos) {
  if (!tabla || ip < 0 || iu < 0 || ip > iu){
    printf("Error en los parametros de entrada median\n");
    return ERR;
  } 

  *pos = ip;
  return 0;
}

/*Función de pivote que devuelve la posición media de la tabla*/
int median_avg(int* tabla, int ip, int iu, int* pos) {
  if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  *pos = (ip + iu) / 2;
  return 0;
}

/*Función de pivote que compara los valores de las posiciones ip, iu y (ip+iu)/2*/
/*Devuelve la posición que contiene el valor intermedio entre los tres*/
int median_stat(int* tabla, int ip, int iu, int* pos) {
  int medio;

  if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  medio = (ip + iu) / 2;

  if ((tabla[ip] >= tabla[iu] && tabla[ip] <= tabla[medio]) ||
      (tabla[ip] <= tabla[iu] && tabla[ip] >= tabla[medio])) {
      *pos = ip;
  } else if ((tabla[iu] >= tabla[ip] && tabla[iu] <= tabla[medio]) ||
              (tabla[iu] <= tabla[ip] && tabla[iu] >= tabla[medio])) {
      *pos = iu;
  } else {
      *pos = medio;
  }

  return 3;  /*3 operaciones básicas adicionales realizadas por median_stat*/
}


/*Función de partición modificada que utiliza la función de pivote especificada*/
int partition2(int* tabla, int ip, int iu, int* pos, int (*pivote)(int*, int, int, int*)) {
  int ob_pivote, temp, pivot, i, j;
  if (!tabla || ip < 0 || iu < 0 || ip > iu) return ERR;

  /* Llamada a la función de pivote*/
  ob_pivote = pivote(tabla, ip, iu, pos);

  /*Intercambiar el pivote con el primer elemento*/
  temp = tabla[ip];
  tabla[ip] = tabla[*pos];
  tabla[*pos] = temp;

  pivot = tabla[ip];
  i = ip + 1;

  for (j = ip + 1; j <= iu; j++) {
      if (tabla[j] < pivot) {
          /*Intercambiar elementos*/
          temp = tabla[j];
          tabla[j] = tabla[i];
          tabla[i] = temp;
          i++;
      }
  }

  /*Colocar el pivote en su posición final*/
  tabla[ip] = tabla[i - 1];
  tabla[i - 1] = pivot;

  *pos = i - 1;  /*Posición final del pivote*/
  return ob_pivote + iu - ip;  /*Operaciones básicas adicionales + operaciones básicas realizadas por partition*/
}

int quicksort(int* tabla, int ip, int iu) {
  int pos, ob, temp, ob_partition, ob1, ob2;
  if (!tabla || ip < 0 || iu < 0 || ip > iu){
    printf("Error en los parametros de entrada quick\n");
    return ERR;
  } 

  if (ip < iu) {
      ob = median(tabla, ip, iu, &pos);
      if (ob == ERR) {
        printf("Error en ob\n");
        return ERR;
      } 

      /*Intercambiar el pivote con el primer elemento*/
      temp = tabla[ip];
      tabla[ip] = tabla[pos];
      tabla[pos] = temp;

      ob_partition = partition2(tabla, ip, iu, &pos, median_stat);
      /*int ob_partition = partition(tabla, ip, iu, &pos);*/
      if (ob_partition == ERR) return ERR;

      ob1=0;
      if(pos-1>ip){
        ob1 = quicksort(tabla, ip, pos - 1);
        if (ob1 == ERR) {
          printf("Error en ob1\n");
          return ERR;
        } 
      }
      ob2=0;
      if(pos+1<iu){
        ob2 = quicksort(tabla, pos + 1, iu);
        if (ob2 == ERR) {
          printf("Error en ob2\n");
          return ERR;
        } 
      }

      if (ob1 == ERR || ob2 == ERR) {
          printf("Error en ob1 o ob2\n");
          return ERR;
      }

      return ob + ob_partition + ob1 + ob2;
  }

  return 0;  /*Caso base: ya está ordenado*/
}
