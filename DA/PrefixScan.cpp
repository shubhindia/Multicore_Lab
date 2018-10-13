

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000


void computeEScan(float* odata, float* idata, const unsigned int len)
{
	odata[0] = 0;
#pragma omp parallel for
	for (unsigned int i = 1; i < len; ++i) {
		odata[i] = idata[i - 1] + odata[i - 1];
	}
	}



 
void computeIScan( float* odata, float* idata, const unsigned int len)   
{   
	odata[0] = idata[0];   
#pragma omp parallel for
	for( unsigned int i = 1; i < len; ++i){   
		odata[i] = idata[i] + odata[i-1];   
	}   
}  

void init_data(float *W, int len)   
{   
	
	int i;  
#pragma omp parallel for
	for (i = 0; i < len; i++) {   
		W[i] = (rand()%100) / 10.0; 
	}   
}   
  
int main(int argc, char* argv[])   
{   
	int i;
	double eStart, eEnd, iStart, iEnd;
	float *startData = new float[N];   
	float *IscanData = new float[N];   
	float *EscanData = new float[N];   

	init_data(startData, N);   

	printf("Starting array:\n");   
	for (i = 0; i < N; i++){   
		printf ("%3.1f ",startData[i]);   
	}   
	printf("\n");
  
	printf("\nExclusive Prefix Scan:\n");   
    eStart = omp_get_wtime();
#pragma omp parallel 
	computeEScan(EscanData, startData, N); 
    eEnd = omp_get_wtime();
	{
#pragma omp parallel for
		for (i = 0; i < N; i++) {
			printf("%3.1f ", EscanData[i]);
		}
	}
	printf("\n");
	printf("Exclusive Prefix Scan time = %f  
seconds\n",eEnd-eStart);

	printf("\nInclusive Prefix Scan:\n");   
 	iStart = omp_get_wtime();
#pragma omp parallel 	
computeIScan(IscanData, startData, N); 
    iEnd = omp_get_wtime();
#pragma omp parallel for 
	for (i = 0; i < N; i++){   
		printf ("%3.1f ",IscanData[i]);   
	}   
	printf("\n");
 	printf("Inclusive Prefix Scan time =  %f seconds\n", 
iEnd-iStart);

	return 0;   
}  

