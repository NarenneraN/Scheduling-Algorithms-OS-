#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>

pthread_t philos[5];
pthread_mutex_t mutex[5] = PTHREAD_MUTEX_INITIALIZER;

void eating(int i){
	int x = i;
	int y = (i+1)%5;
	while (1)
	{
		printf("Philos %d is thinking\n",x);
		pthread_mutex_lock(&mutex[x]);
		printf("stick %d locked by philos %d\n",x,x);
		if(pthread_mutex_trylock(&mutex[y]) == 0){
			printf("stick %d locked by philos %d\n",y,x);
			//eating
			printf("Eating by philos %d\n",x);
			sleep(2);
			//unlocking
			pthread_mutex_unlock(&mutex[x]);
			printf("stick %d unlocked by philos %d\n",x,x);
			pthread_mutex_unlock(&mutex[y]);
			printf("stick %d unlocked by philos %d\n",y,x);
			printf("Philos %d finished eating\n",x);
			break;
		}
		else{
			printf("Trylock failed by Philos %d for lock %d\n",x,y);
			pthread_mutex_unlock(&mutex[x]);
			printf("stick %d unlocked by philos %d in trylock\n",x,x);
			sleep(1);
		}
	}
	return 0;
}

int main()
{
	int n[5];
	for(int i=0;i<5;i++){
		if(pthread_create(&philos[i],NULL,eating,i) != 0){
			perror("Thread Not Created!");
		}
	}
	for(int i=0;i<5;i++){
		pthread_join(philos[i],NULL);
	}
	return 0;
}
