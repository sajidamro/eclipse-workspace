
/* *Lab1: Multiply two matrices using OpenMP
 * *Student Name: Sajid Mahmood
 * *Course Name: EE8218 Parallel Computing
 * *Instructor Name: Dr. Nagi Mekhiel
*/

//#define _POSIX_C_SOURCE 199309L

#include "iostream"
#include <stdlib.h>
#include <omp.h>
#include <ctime>
#include <tchar.h>
#include <math.h>
#include <chrono>


using namespace std;

/*
*Instance Variables of Matrix1, Matrix2
*Instance and Resultant Matrix
*Instance *Also, the length of the square matrix
*/
const int sizeOfMatrix = 2048;
const int numberOfThreads = 8;
const char debug = 0 ;
int sizeMatrix=0;

int matrix1[sizeOfMatrix][sizeOfMatrix];
int matrix2[sizeOfMatrix][sizeOfMatrix];
int result [sizeOfMatrix][sizeOfMatrix];

/*
*Initialize()
*THis method initializes both matrices (MATRIX1 and MATRIX2) with Math random values 0-9
*Update the values of both matrices, Matrix1 and Matrix2
*/

void initialize()
{ for (int i = 0; i < sizeOfMatrix; i++)
	{ for (int j = 0; j < sizeOfMatrix; j++)
		{
			matrix1[i][j] = rand() % 100;
			matrix2[i][j] = rand() % 100;
		}
	}
}

void initializeMatrix(int size)
{ for (int i = 0; i < size; i++)
	{ for (int j = 0; j < size; j++)
		{
			matrix1[i][j] = rand() % 100;
			matrix2[i][j] = rand() % 100;
			result[i][j]= 0;
		}
	}
}

/*Void MultiplyMatrix
*method multiplies both matrices (MATRIX1 and MATRIX2) without using parallelism or OpenMP
*Store the result of multiplication into the resulant MATRIX.
*/
void multiplyMatrix()
{
	for (int i = 0; i < sizeOfMatrix; i++)
		{
			for (int j = 0; j < sizeOfMatrix; j++)
				{
					for (int k = 0; k < sizeOfMatrix; k++)
					{ result[i][j] += matrix1[i][k] * matrix2[k][j];
					}
				}
		}
}

void multiplyMatrixSize(int size)
{
	for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				{
					for (int k = 0; k < size; k++)
					{ result[i][j] += matrix1[i][k] * matrix2[k][j];
					}
				}
		}
}
/*
*DisplayMatrix
*optional method available to display any matrix
*Requires a matrix of specific size *Display the whole matrix
*/
void displayMatrix(int matrixToDisplay[sizeOfMatrix][sizeOfMatrix])
{
	for (int i = 0; i < sizeOfMatrix; i++)
		{
			for (int j = 0; j < sizeOfMatrix; j++)
				{
					std::cout << matrixToDisplay[i][j] << " ";
				}
			std::cout << " \n" << endl;
		}
}
/*
*MultiplyMatrix
*THis method multiplies both matrices (MATRIX1 and MATRIX2) using parallelism or OpenMP
*Store the result of multiplication into the resulant MATRIX.
*/
void multiplyParallel(char numberThreads)
{
	//cout << "number of threads are set to: " << omp_get_num_threads()<< endl;
	 /* Get the number of processors */
	//cout << "\nNumber of processors available " << omp_get_num_procs() <<endl;

#pragma omp parallel for num_threads(numberThreads)

	for (int i = 0; i < sizeOfMatrix; i++)
			{
				if(i==0 && debug == 1)
					{
						printf("number of active threads");
					}
				else if(debug == 1)
					{
						printf("%i ", omp_get_num_threads());
						printf("%i \n\r", omp_get_thread_num());
					}
				for (int j = 0; j < sizeOfMatrix; j++)
					{
						for (int k = 0; k < sizeOfMatrix; k++)
							{
								result[i][j] += matrix1[i][k] * matrix2[k][j];
							}
					}
			}
}

void multiplyParallelSize(char numberThreads, int size)
{
	//cout << "number of threads are set to: " << omp_get_num_threads()<< endl;
	 /* Get the number of processors */
	//cout << "\nNumber of processors available " << omp_get_num_procs() <<endl;

#pragma omp parallel for num_threads(numberThreads)

	for (int i = 0; i < size; i++)
			{
				if(i==0 && debug == 1)
					{
						printf("number of active threads");
					}
				else if(debug == 1)
					{
						printf("%i ", omp_get_num_threads());
						printf("%i \n\r", omp_get_thread_num());
					}
				for (int j = 0; j < size; j++)
					{
						for (int k = 0; k < size; k++)
							{
								result[i][j] += matrix1[i][k] * matrix2[k][j];
							}
					}
			}
}

/* *Main of the program which is executed on RUNTIME */

int main(int argc, _TCHAR* argv[])
{

	//Commands for initialization of Matrices

	FILE *log_file;
		/** Start Logging into file**/
		log_file = fopen ("Matrix_Multi.log","a+");

		//clock_gettime();

for(int x=1; x <= 11 ;x++)
	{
		sizeMatrix = pow(2,x);
		fprintf(log_file,"Size of the Matrix = %i x %i \n\r", sizeMatrix, sizeMatrix);
		printf("Generating Two Square Matrices of Size:  %i x %i \n", sizeMatrix, sizeMatrix);
		initializeMatrix(sizeMatrix);
		//initialize();

		//Commands for Multiplying matrices without Parallelism and time the algorithm
			cout << "\n\nMuliplying Two matrices without Parallelism or OpenMP" << endl;
			fprintf(log_file,"\n\tMuliplying Two matrices without Parallelism or OpenMP \n\r");

			auto start = std::chrono::system_clock::now();
			multiplyMatrixSize(sizeMatrix);
			auto end = std::chrono::system_clock::now();

			std::chrono::duration <double> elapsed_seconds = end-start;

			std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

			fprintf(log_file,"\n\tThe Multiplication took TIME in milliseconds: %f \n\r", elapsed_seconds.count());

		//Commands for Multiplying matrices with Parallelism and time the algorithm
			cout << "\n\nMuliplying Same Matrices with Parallelism using OpenMP" << endl;
			fprintf(log_file,"\n\tMuliplying Same Matrices with Parallelism using OpenMP \n\r");

				//multiplyParallel(maxNumThreads);
			for(int m=2; m <= numberOfThreads; m++)
				{
					auto start = std::chrono::system_clock::now();
					multiplyParallelSize( m , sizeMatrix);
					auto end = std::chrono::system_clock::now();

					std::chrono::duration <double> elapsed_seconds = end-start;

					std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << "\t by using Thread Number: " << m << endl;

					fprintf(log_file,"\n\tThe Multiplication took TIME in milliseconds: %f by using Thread numbers: %i\n\r", elapsed_seconds.count(),m);
				}
	}
		printf("Iteration completed");
		fclose(log_file);// Closing the log file as well
	return 0;
}


