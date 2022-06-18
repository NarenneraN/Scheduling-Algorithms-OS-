#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("-----SCAN Scheduling-----\n");
	int initial=0,end;
	printf("Enter the End Bound of the cylinder: "); scanf("%d",&end);

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

	//reading the direction
	int direction;
	printf("\nEnter head direction:\n1.Towards Left\n2.Towards Right\nEnter(1/2): "); scanf("%d",&direction);

	//sorting the request array
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(q[i] > q[j]){
				int temp = q[j];
				q[j] = q[i];
				q[i] = temp;
			}
		}
	}
	
	//finding temp head location in the sorted array
	int location;
	for(int i=0;i<n;i++){
		if(head < q[i]){
			location = i-1;
			break;
		}
	}

	//calculation of total seek time
	int seek = 0;
    //towards left
	if(direction==1){
		printf("\nHead Movement: %d ",head);
		for(int i = location; i >= 0; --i){
			seek = seek + abs(head-q[i]);
			head = q[i];
			printf("%d ",head);
		}
		seek = seek + abs(head-0);
		head = 0;
		for (int i = (location+1); i < n; i++){
			printf("%d ",head);
			seek = seek + abs(q[i]-head);
			head = q[i];
		}
		printf("%d ",head);

		printf("\nThe total Seek time: %d\n",seek);
	} //towards right
	else{
		printf("\nHead Movement: %d ",head);
		for(int i = (location+1); i < n; i++){
			seek = seek + abs(q[i]-head);
			head = q[i];
			printf("%d ",head);
		}
		seek = seek + abs(end-head);
		head = end;
		for (int i = location; i >= 0; --i){
			printf("%d ",head);
			seek = seek + abs(head-q[i]);
			head = q[i];
		}
		printf("%d ",head);

		printf("\nThe total Seek time: %d\n",seek);
	}
	
	return 0;
}
