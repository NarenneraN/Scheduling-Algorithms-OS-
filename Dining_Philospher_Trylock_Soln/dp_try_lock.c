/******************************************************************************

Dining Philospher :-
5 Philosphers 
5 Chopsticks
5 Food

*******************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t chopsticks[5];//0,1,2,3,4

void* eating(int i)
{
    int left,right;
    printf("Philospher - %d --> Waiting \n",i);
    left=i;
    right=(i+1)%5;
    while(1)
    {
        printf("Philospher - %d --> Locked Left \n",i);
        pthread_mutex_lock(&chopsticks[right]);
        if(pthread_mutex_trylock(&chopsticks[left])==0)
        {
            break;
        }
        printf("Philospher - %d --> Failed To Lock Right \n",i);
        pthread_mutex_unlock(&chopsticks[right]);
        sleep(1);
    }
    printf("Philospher - %d --> Locked Right \n",i);
    printf("Philospher - %d --> Eating \n",i);
    sleep(1);
    pthread_mutex_unlock(&chopsticks[left]);
    pthread_mutex_unlock(&chopsticks[right]);
    
}
int main()
{
    pthread_t th[5]; //Represents Philosphers
    for(int i=0;i<5;i++)
    {
        pthread_mutex_init(&chopsticks[i],NULL);
    }
    for(int i=0;i<5;i++)
    {
        if(pthread_create(&th[i],NULL,&eating,i)!=0)
        {
            perror('Thread Not Created!!');
        }
    }
    for(int i=0;i<5;i++)
    {
        if(pthread_join(th[i],NULL)!=0){
            perror("Couldn't Join");
        }
    }
    for(int i=0;i<5;i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }
}
