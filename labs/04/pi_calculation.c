/*
	Link to graphic: https://drive.google.com/file/d/1sY4xJRMhgOHO-5QQ6T-lP9CllhFv3XyX/view?usp=sharing
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


#define POINTS 10000
#define SEED 35791246

int num_threads; //number of threads to create
long points_per_thread;
long inside=0;

void *monteCarlo(void *t_id){
	double x,y;
	int *count = (int *)malloc(sizeof(int)); //num of points in 1st quadrant of unit circle
	double z;
	int i;
	
	//initialize random nums
	*count =0;
	//unsigned int random = rand();
	srand(SEED);
	for(i=0; i<points_per_thread; i++){
		//create random number [0,1]
		x = rand() / ((double)(unsigned) RAND_MAX +1);
		y = rand() / ((double)(unsigned) RAND_MAX +1);
		z = x*x + y*y;
		if(z<=1){
			*count+=1;
			//inside++;
		}
	}
	
	pthread_exit((void *) count);
}

int main(int argc, const char *argv[]){

//	clock_t start, end;
//	double cpu_time_used;
//	start = clock();
	
	if(argc!=2){
		printf("Threads were not specified\n");
		return 1;
	}
	
	num_threads=atoi(argv[1]);
	
	if(num_threads==0){
		printf("Number of threads has to be greater than 0 \n");
		return 0;
	}
	
	points_per_thread = POINTS/num_threads;
	
	pthread_t threads[num_threads];
	
	int rc;
	int t;
	
	for(t=0; t<num_threads; t++){
		rc = pthread_create(&threads[t], NULL, monteCarlo, (void *)(intptr_t) t);
		
		if(rc){
			printf("ERROR CREATING THREADS \n");
			return 1;
		}
	}
	
	double pi;
	void *count_thread;
	
	for(t=0; t<num_threads; t++){
		pthread_join(threads[t], &count_thread);
		inside += * (long *) count_thread;
	}
	
	pi = (4.00 * (double)inside ) / ((double)points_per_thread * num_threads);

	printf("PI: %f \n", pi);
	
//	end = clock();
//	cpu_time_used = ((double)(end - start)) /  CLOCKS_PER_SEC;
//	printf("Time used with %d threads is %f \n",num_threads, cpu_time_used);
	
	return 0;
}
