/*
 * main.c
 *
 *  Created on: Sep 9, 2018
 *      Author: Sajid
 */

/* Work Sharing construct
https://computing.llnl.gov/tutorials/openMP/#DO

Distributes an array of elements across threads, where each
element is passed as a parameter to a function to be evaluated

*/

#include <omp.h>
#include <stdio.h>
#include <time.h>

#define N 5
#define CHUNKSIZE 100

/* dummy function*/
float myfun(float a)
{
  return a*a*a;
}

int main (int argc, char **argv)
{

  int i, chunk, tid ;

  float a[N], b[N];
  char flagAssign = 0;

  // assign values to to Martrix a
  for (i=0; i < N; i++)
    {
	  a[i] = i * 1.0;

	  if (flagAssign == 0)		{		printf("Matrix A [");
		  	  	  	  	  	  	  	  	flagAssign = 1;				}

	  else if(flagAssign > 0)  	  {		printf("%f  ", a[i]);		}

	  if (i >= (N-1))	  {		printf("]\n");		}

    }


  /* Get the number of processors */
  printf("Number of processors available:: %d\n",omp_get_num_procs());

  /* Set the chunk size*/
  chunk = CHUNKSIZE;

  /* Set the number of threads to the number of processors*/
  omp_set_num_threads(omp_get_num_procs());

  tid = omp_get_thread_num();

  printf ("Number of threads are set to: %d\n\r", tid);

#pragma omp parallel shared(a,b,chunk) private(i)
  {

#pragma omp for schedule(dynamic,chunk)
    for (i=0; i< N; i++)
      {
        b[i] = myfun(a[i]);
      }
  }  /* end of parallel section */

  printf("For evaluation completed, the result has been stored in array B\n");

  return 0;
}

