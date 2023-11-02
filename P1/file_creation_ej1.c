/***********************************************/
/* Program: exercise1     Date:                */
/* Authors:                                    */
/*                                             */
/* Program that generates two random nunmbers  */
/* between two given numbers                   */
/*                                             */
/* Input: Command Line                         */
/* -limInf: lower limit                        */
/* -limSup: upper limit                        */
/* -numN: ammount of numbers                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int inf, sup, num, j;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }
  printf("File with the number obtained\n");
  printf("Done by: Iker González Sánchez\n");
  printf("Group: 1261\n");

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }

  int *numbers = (int*)malloc((sup-inf+1)*sizeof(int));
  if (numbers == NULL) {
      return -1;
  }

  for (i = 0; i < sup-inf+1; i++) {
      numbers[i] = 0;
  }

  /* print data */
  for(j = 0; j < num; j++) { 
    int number = random_num(inf, sup);
    numbers[number-inf]++;
  }


  FILE *f = fopen("Datos.txt", "w");
  if (f == NULL) {
      return -1;
  }
  for(i = 0; i < sup-inf+1; i++) {
      fprintf(f, "%d\t %d\n", i+inf, numbers[i]);
  }

  return 0;
}

