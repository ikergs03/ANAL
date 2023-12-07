/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdio.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  int num, dif;

  if(inf > sup) return ERR;

  dif = sup - inf;

  num = rand() % (dif+1) + inf;

  return num;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i = 0, randomNum = 0, aux = 0;
  int *perm = NULL;

  if(N < 1) return NULL; 

  perm = (int*)malloc(N*sizeof(int));
  if (perm == NULL) {
    return NULL;
  }

  for (i = 0; i < N; i++) {
    perm[i] = i;
  }

  for (i = 0; i < N; i++) {
    randomNum = random_num(i, N-1);
    aux = perm[i];
    perm[i] = perm[randomNum];
    perm[randomNum] = aux;

  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i = 0;
  int **perm = NULL;

  if(n_perms < 1 || N < 1) return NULL;

  perm = (int**)malloc(n_perms*sizeof(int*));

  if (perm == NULL) {
    return NULL;
  }

  for (i = 0; i < n_perms; i++) {
    perm[i] = generate_perm(N);
    if (perm[i] == NULL) {
      return NULL;
    }
  }

  return perm;
}
