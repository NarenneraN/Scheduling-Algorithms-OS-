#include<stdio.h>
struct process
{
    int id,AT,BT,WT,TAT;
};

int queue[100];
int front=-1;
int rear=-1;


void enqueue(int n)
{
    if(front==-1)
     front=0;
    rear=rear+1;
    queue[rear]=n;
}

int dequeue()
{
    int n;
    n=queue[front];
    front=front+1;
    return n;
}

int main()
{
    int n,TQ,p,TIME=0,check=0,bt,at;
    int temp[10],exist[10]={0};
    float total_wt=0,total_tat=0,Avg_WT,Avg_TAT;
    printf("Enter the number of the process: "); scanf("%d",&n);
    struct process a[n];
    for(int i=0;i<n;i++)
    {
        a[i].id=i;
        while(check==0)
        {
           check=1;
           printf("Enter Burst Time For Process - %d: ",a[i].id);
           scanf("%d",&bt); 
           if(bt<0)
           {
               printf("Burst Time Should Not be Negative\n");
               check=0;
           }
           else if(bt>10)
           {
               printf("Please enter below 10\n");
               check=0;
           }
        }
        while(check==1)
        {
            check=0;
            printf("Enter Arrival Time Time For Process - %d: ",a[i].id);
            scanf("%d",&at);
            if(at<0)
            {
                printf("Arrival Time Should Not be Negative\n");
                check=1;
            }
        }
        a[i].BT = bt;
        a[i].AT = at;
        temp[i] = bt;       
    }

    printf("Enter the time quantum\n");
    scanf("%d",&TQ);

    enqueue(0);
    exist[0]=1;

    while(front<=rear)
    {
        p=dequeue();
        if(a[p].BT>=TQ)
        {
            a[p].BT=a[p].BT-TQ;
            TIME=TIME+TQ;
        }
        else
        {
            TIME=TIME+a[p].BT;
            a[p].BT=0;
        }
        
        for(int i=0;i<n;i++)
        {
            if(exist[i]==0 && a[i].AT<=TIME)
            {
                enqueue(i);
                exist[i]=1;
            }
        }
        
        if(a[p].BT==0)
        {
            a[p].TAT=TIME-a[p].AT;
            a[p].WT=a[p].TAT-temp[p];
            total_tat=total_tat+a[p].TAT;
            total_wt=total_wt+a[p].WT;
        }
        else
        {
            enqueue(p);
        }
    }
    
    Avg_TAT=total_tat/n;
    Avg_WT=total_wt/n;

    printf("----------------------------------------------------------------------------------\n");
    printf("| %12s | %12s | %12s | %18s | %12s |\n","PROCESS ID","BURST TIME","ARRIVAL TIME","Remaining TIME","WAITING TIME");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i+=1)
    {
        printf("| %12d | %12d | %12d | %18d | %12d |\n",a[i].id,temp[i],a[i].AT,a[i].TAT,a[i].WT);
    }
    printf("----------------------------------------------------------------------------------\n");

    printf("Average waiting time of the processes is : %f\n",Avg_WT);
    printf("Average turn around time of the processes is : %f\n",Avg_TAT);
    return 0;
}