/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include<stdlib.h>
int main()
{
    //Process :
    int n;
    //Resources :
    int m;
    //Alphabets
    int alpha[10]={'A','B','C','D','E','F','G','H','I','J'};
    int curr=0;
    scanf("%d",&n);
    scanf("%d",&m);
    int max[n][m],available[m],need[n][m],allocation[n][m],work[m],sequence[n],flag[n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("Enter Max Instance of Resources for Process-%d for the Resource-%c :  ",i,alpha[j]);
            scanf("%d",&max[i][j]);
        }
    }
    printf("Max Matrix :-  \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("Enter Aloccation of Resources for Process-%d for the Resource-%c :  ",i,alpha[j]);
            scanf("%d",&allocation[i][j]);
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
    printf("Allocation Matrix :-  \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%d ",allocation[i][j]);
        }
        printf("\n");
    }
    printf("Need Matrix :-  \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    for(int j=0;j<m;j++)
    {
        printf("Enter Available resource for Resource type - %c : ",alpha[j]);
        scanf("%d",&available[j]);
    }
    printf("Available Matrix :- \n");
    for(int i=0;i<n;i++)
    {
        flag[i]=0;
        sequence[i]=0;
    }
    int pno;
    printf("Enter The Process Number Which Requests : ");
    scanf("%d",&pno);
    int request[m];
    printf("Enter Request Matrix for that :-");
    for(int j=0;j<m;j++)
    {
        scanf("%d",&request[j]);
    }
    printf("Request Matrix :- \n");
    for(int j=0;j<m;j++)
    {
        printf("%d ",request[j]);
    }
    printf("\n");
    //first Check Whether Request<=Need , Request<=Available
    for(int j=0;j<m;j++)
    {
        if(request[j]>need[j] || request[j]>available[j])
        {
            printf("Not A Safe Request ! Will Lead to Deadlock");
            exit(0);
        }
    }
    //Alter Need Matrix 
    //Alter Allocation Matrix 
    //Alter Available Mxtrix
    for(int j=0;j<m;j++)
    {
        need[pno][j]=need[pno][j]-request[j];
        allocation[pno][j]=allocation[pno][j]+request[j];
        available[j]=available[j]-request[j];
    }

    //Algorithm Starts ----
    for(int q=0;q<n;q++)
    {
        for(int i=0;i<n;i++)
        {
            if (flag[i]==0)
            {
                int check=0;
                for(int j=0;j<m;j++)
                {
                  if(need[i][j]>available[j])
                  {
                      check=1;
                      break;
                  }
                }
                if(check==0)
                {
                    sequence[curr]=i;
                    curr++;
                    // printf("\n ---- %d ----",i);
                    for(int p=0;p<m;p++)
                    {
                        available[p]+=allocation[i][p];
                    }
                    flag[i]=1;
                }
                
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        // printf("%d",flag[i]);
        if(flag[i]==0)
        {
            printf("System violates safety state ! It will result into Deadlock state \n");
            exit(0);
        }
    }
    printf("One of the Possible Safety Sequence :-  \n");
    for(int i=0;i<n;i++)
    {
        printf("Process - %d \n",sequence[i]);
    }

}
