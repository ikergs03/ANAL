/**
 *
 * Descripcion: Headers for time measurement functions 
 *
 * Fichero: times.h
 * Author: Carlos Aguirre / Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2019
 *
 */

/* type definitions */
typedef struct time_aa {
  int N;           /* size of each element */
  int n_elems;     /* number of elements to average */
  double time;   /* average clock time */
  double average_ob; /* average number of times that the OB is executed */
  int min_ob;      /* minimum of executions of the OB */
  int max_ob;      /* maximum of executions of the OB */
} TIME_AA, *PTIME_AA;

short generate_search_times(pfunc_search method, pfunc_key_generator generator, 
                                int order, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_times);

short average_search_time(pfunc_search metodo, pfunc_key_generator generator,
                              int order,
                              int N, 
                              int n_times,
                              PTIME_AA ptime);




