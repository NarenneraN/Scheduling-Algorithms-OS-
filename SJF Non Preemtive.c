#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
struct Process {
  int id;
  int bursttime;
  int finished;
  int waitingtime;
  int completiontime;
};
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}
int main()
{
    int num,bt,at,check=0;
    struct Process *p;
    printf("Enter Total No.of Process :- ");
    scanf("%d",&num);
    p = (struct Process*)malloc(num*sizeof(struct Process));
    printf("%d process getting created with id's 1 to %d \n",num,num);
    
    for(int i=0;i<num;i+=1)
    {
        check=0;
        p[i].id=i+1;
        p[i].finished=0;
        while(check==0)
        {
           check=1;
           printf("Enter Burst Time For Process - %d :- ",p[i].id);
           scanf("%d",&bt); 
           if(p[i].bursttime<0)
           {
               printf("Burst Time Should Not be Negative\n");
               check=0;
           }
           else if(p[i].bursttime>10)
           {
               printf("Please enter below 10\n");
               check=0;
           }
        }
        p[i].bursttime=bt;
        
    }

    int tym=0,finished=0,tot_burst=0;
    for(int i=0;i<num;i++)
    {
     tot_burst+=p[i].bursttime;   
    }
    int burst_all[num];
    for(int i=0;i<num;i++)
    {
       burst_all[i]=p[i].bursttime;
    }
    selectionSort(burst_all,num);
        for(int i=0;i<num;i++)
        {
            for(int j=0;j<num;j++)
            {
                if(p[j].bursttime==burst_all[i] && p[j].finished==0)
                {
                    int temptym=0;
                    while(temptym!=p[j].bursttime)
                    {
                      temptym+=1;
                    }
                    tym+=temptym;
                    printf("%d\n",tym);
                    p[j].completiontime=tym;
                    p[j].waitingtime=p[j].completiontime-p[j].bursttime;
                    p[j].finished=1;
                    finished+=1;
                    break;
                }
            }
        }

    printf("----------------------------------------------\n");
    printf("| %12s | %12s | %12s |\n","PROCESS ID","BURST TIME","WAITING TIME");
    printf("----------------------------------------------\n");
    for(int i=0;i<num;i+=1)
    {
       printf("| %12d | %12d | %12d |\n",p[i].id,p[i].bursttime,p[i].waitingtime);
    }
    printf("----------------------------------------------\n");
    return 0;
}