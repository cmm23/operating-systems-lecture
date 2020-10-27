#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

int totalBottles = 1000;
int bottlesSold=0;
int seller[5];
int sellers=5;

int rando[5];
bool t[6]={false,false,false,false,false,false};



pthread_mutex_t mutex;



void sellBottles(intptr_t *t_id){
	intptr_t t_id1 = (intptr_t)t_id;
	
	//int i=0;
	int sell=t_id1;
	for(int i=1; i<6 || t[sell]!=true; i++){
		//printf("Im here %d \n", sell);
		//printf("Random numbers are %d \n",rando[i-1]);
		if(rando[i-1]+seller[sell] <=200 && rando[i-1]!=0){
			seller[sell]+=rando[i-1];
			bottlesSold+=rando[i-1];
			rando[i-1]=0;
			printf("Seller %d", sell);
			printf(" has sold %d ", seller[sell]);
			printf(" bottles \n");
			t[sell]=true;
			break;
		}
		t[sell]=true;	
	}
	
}

void *threadFunc(void *i){
	intptr_t t_id = (intptr_t) i;
	
	//printf("Inside thread %zd \n",t_id);
	
	//LOOP: printf("Trying to access %zd \n",t_id);
	
	pthread_mutex_lock(&mutex);
	
	//printf("BLOCK BY %zd \n", t_id);
	
	if(bottlesSold < 1000 && t[t_id]==false){
		sellBottles((intptr_t *)t_id);
	//	pthread_mutex_unlock(&mutex);
	}
	//else{
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	//}
}

void generateRandom(){
	//srand(time(0));
	for(int i=0; i<5; i++){
		rando[i] = (rand()%(200)+1);
		//printf("Random number %d %d \n",i,rando[i]);
	}
	
	
}

int main(void){
	pthread_mutex_init(&mutex, NULL);
	srand(time(0));
	//Create threads
	//j is counting the bottles of clients
	for(int j=0; j<5; j++){
		generateRandom();
		t[1]=false;
		t[2]=false;
		t[3]=false;
		t[4]=false;
		t[5]=false;
		
		printf("ROUND %d \n", j+1);
		pthread_t threads[sellers];
		
		//i counts the sellers
		//create threads
		for(int i =0; i<sellers; i++){
			pthread_create(&threads[i],NULL,threadFunc,(void *)(intptr_t)(i+1));		
		}
		
		//waits for threads to be completed
		for(int i=0; i<sellers; i++){
			pthread_join(threads[i],NULL);
			
		}
	
	}
	printf("------------------------------ \n");
	printf("BOTTLES SOLD \n");
	for(int i=0; i<sellers; i++){
		printf("Seller %d sold %d bottles \n",i+1, seller[i+1]);
	}

	
	printf("Total of bottles sold is %d \n",bottlesSold);
	return 0;
}
