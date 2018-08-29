#include<stdio.h>
#include<omp.h>
int main()
{
#pragma omp parallel
{
double s = omp_get_wtime();
printf("Hello World\n");
double e = omp_get_wtime();
printf("Time Taken = %f Seconds\n",e-s);
}
}
