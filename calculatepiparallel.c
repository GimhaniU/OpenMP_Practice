#include <omp.h>
#include <stdio.h>
#define NUM 2
static long num_steps= 100000;
double step;
double pi,sum[NUM];

int main()
{
	
	step= 1.0/(double)num_steps;
	double beg=omp_get_wtime();
	#pragma omp parallel num_threads(4)
	{	
	int ID=omp_get_thread_num();
	int total=omp_get_num_threads();
	int start=ID*num_steps/total;
	int end=(ID+1)*num_steps/total;
	int i;
        double x,my_sum=0.0;
        for(i=start;i<end;i++){
                x=(i+0.5)*step;
                my_sum=my_sum+ 4.0/(1.0+x*x);
        }
		sum[ID]=my_sum;	
	}

	double tot=0;
	int j;
	for(j=0;j<NUM;j++){
		tot+=sum[j];
	}
        pi=step*tot;
	double stop=omp_get_wtime();
        printf("%f : time taken : %f",pi,stop-beg);
}


