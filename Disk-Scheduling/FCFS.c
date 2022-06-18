#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("-----FCFS Scheduling-----\n");
	//scanning the request
	int n;
	printf("Enter the No.of Requests: "); scanf("%d",&n);
	int q[n];
	for(int i=0; i<n; i++){
		printf("Request %d: ",i+1); scanf("%d",&q[i]);
	}

	//reading current head position
	int head;
	printf("Enter current position of head: "); scanf("%d",&head);

	//calculation of total seek time
	int seek = 0;
	printf("Head Movement: ");
	for(int i=0;i<n;i++){
		printf("%d ",head);
		seek = seek + abs(q[i]-head);
		head = q[i];
	}
	printf("\nThe total Seek time: %d\n",seek);
	return 0;
}
