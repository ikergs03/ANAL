/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo,
                           int n_perms,
                           int N,
                           PTIME_AA ptime)
{
  if(!metodo || n_perms < 1 || N < 1 || !ptime) return ERR;

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = 0;
  ptime->average_ob = 0;
  ptime->min_ob = -1;
  ptime->max_ob = 0;

  int i=0;
  short status = OK;


  int **perm = generate_permutations(n_perms, N);
  if(!perm) return ERR;

  for(i=0; i<n_perms && status==OK; i++) {

    clock_t t = clock();
    int ob = metodo(perm[i], 0, N-1);
    t = clock() - t;

    if(ob == ERR){
      status = ERR;
    } 

    ptime->time += ((double)t);
    ptime->average_ob += ob;

    if(ptime->min_ob == -1 || ob < ptime->min_ob) ptime->min_ob = ob;
    if(ob > ptime->max_ob) ptime->max_ob = ob;
  }

  ptime->time /= n_perms;
  ptime->average_ob /= n_perms;
  
  for(i=0; i<n_perms; i++) free(perm[i]);
  free(perm);
  return status;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
                             int num_min, int num_max,
                             int incr, int n_perms)
{
  if(!method || !file || num_min < 1 || num_max < num_min || incr < 1 || n_perms < 1) return ERR;

  int veces = (num_max - num_min)/incr + 1, i;
  short status = OK;

  PTIME_AA ptime = (PTIME_AA)malloc(veces*sizeof(TIME_AA));
  if(!ptime) return ERR;

  for(i=0; i<veces && status == OK; i++){
    status = average_sorting_time(method, n_perms, num_min + i*incr, &ptime[i]);
  }

  if(status == OK) status = save_time_table(file, ptime, veces);

  free(ptime);

  return status;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  if(!file || !ptime || n_times < 1) return ERR;

  FILE *f = fopen(file, "w");
  int status = OK, i;
  if(!f) return ERR;

  /**if(fprintf(f, "%10s %10s %12s %10s %10s\n","N","time","average_ob", "min_ob", "max_ob")<0) status = ERR;
  for(i = 0; i<n_times && status == OK; i++){
    if(fprintf(f, "%10d %10.2f %12.2f %10d %10d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob)<0) 
      status = ERR;
  }*/
  
  /**if(fprintf(f, "%s,%s,%s,%s,%s\n","N","time","average_ob", "min_ob", "max_ob")<0) status = ERR;*/
  for(i = 0; i<n_times && status == OK; i++){
    if(fprintf(f, "%d,%f,%f,%d,%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob)<0) 
      status = ERR;
  }

  fclose(f);
  return status;
}



short average_search_time(pfunc_search method, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime){
  if (!method || !generator || !ptime || N < 1 || n_times < 1) return ERR;

  ptime->N = N;
  ptime->n_elems = n_times;
  ptime->time = 0;
  ptime->average_ob = 0;
  ptime->min_ob = -1;
  ptime->max_ob = 0;


  PDICT pdict = init_dictionary(N, order);
  if(!pdict) return ERR;

  int *perm = generate_perm(N);
  if(!perm) return ERR;

  if(order == SORTED) quicksort(perm, 0, N-1);

  massive_insertion_dictionary(pdict, perm, N);

  int *keys = (int*)malloc(n_times*N*sizeof(int));
  if(!keys) return ERR;

  generator(keys, n_times*N, N);

  int i, ob, pos;
  for(i=0; i<n_times*N; i++){
    clock_t t = clock();
    ob = search_dictionary(pdict, keys[i], &pos, method);
    t = clock() - t;

    if(ob == ERR) return ERR;

    ptime->time += ((double)t);
    ptime->average_ob += ob;

    if(ptime->min_ob == -1 || ob < ptime->min_ob) ptime->min_ob = ob;
    if(ob > ptime->max_ob) ptime->max_ob = ob;
  }

  ptime->time /= n_times*N;
  ptime->average_ob /= n_times*N;

  free_dictionary(pdict);
  free(perm);
  free(keys);

  return OK;
}


short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char *file, int num_min, int num_max, int incr, int n_times){
  if(!method || !generator || !file || num_min < 1 || num_max < num_min || incr < 1 || n_times < 1) return ERR;

  int veces = (num_max - num_min)/incr + 1, i;
  short status = OK;

  PTIME_AA ptime = (PTIME_AA)malloc(veces*sizeof(TIME_AA));
  if(!ptime) return ERR;

  for(i=0; i<veces && status == OK; i++){
    status = average_search_time(method, generator, order, num_min + i*incr, n_times, &ptime[i]);
  }

  if(status == OK) status = save_time_table(file, ptime, veces);

  free(ptime);

  return status;
}
