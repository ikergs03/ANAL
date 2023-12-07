/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order){
	PDICT pdict;
  pdict = (PDICT)malloc(sizeof(DICT));
  if(!pdict) return NULL;

  pdict->size = size;
  pdict->order = order;
  pdict->n_data = 0;
  pdict->table = (int*)malloc(size*sizeof(int));
  if(!pdict->table) {
    free(pdict);
    return NULL;
  }

  return pdict;
}

void free_dictionary(PDICT pdict){
	if(pdict) {
    if(pdict->table) free(pdict->table);
    free(pdict);
  }

  return;
}

int insert_dictionary(PDICT pdict, int key){
  int obs=0;

	if(!pdict) return ERR;

  if(pdict->n_data == pdict->size) return ERR;

  pdict->table[pdict->n_data] = key;
  pdict->n_data++;

  if(pdict->n_data > 1 && pdict->order == SORTED) {
    int A = pdict->table[pdict->n_data-1];
    int j = pdict->n_data-2;
    while(j >= 0 && pdict->table[j] > A) {
      pdict->table[j+1] = pdict->table[j];
      obs++;
      j--;
    }
    if(j >= 0) obs++;
    pdict->table[j+1] = A;
  }

  return obs;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys){
	int i, obs = 0, aux;

  if(!pdict || !keys || n_keys < 1) return ERR;

  for(i = 0; i < n_keys; i++) {
    aux = insert_dictionary(pdict, keys[i]);
    if(aux == ERR) 
      return ERR;
    else
      obs += aux;
  }

  return obs;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){
	if(!pdict || !method) return ERR;

  return method(pdict->table, 0, pdict->n_data-1, key, ppos);
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos){
	int M;
  if(F > L) {
    *ppos = NOT_FOUND;
    return 0;
  }
  M = (F+L)/2;
  if(table[M] == key) {
    *ppos = M;
    return 1;
  }
  else if(table[M] > key) 
    return 2 + bin_search(table, F, M-1, key, ppos);
  else 
    return 2 + bin_search(table, M+1, L, key, ppos);
}

int lin_search(int *table,int F,int L,int key, int *ppos){
	int i;
  for(i = F; i <= L; i++) {
    if(table[i] == key) {
      *ppos = i;
      return i-F+1;
    }
  }
  *ppos = NOT_FOUND;
  return i-F;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos){
	int obs;

  obs = lin_search(table, F, L, key, ppos);
  if(*ppos != NOT_FOUND && *ppos > F) {
    int aux = table[*ppos];
    table[*ppos] = table[*ppos-1];
    table[*ppos-1] = aux;
    (*ppos)--;
  }
  return obs;
}


