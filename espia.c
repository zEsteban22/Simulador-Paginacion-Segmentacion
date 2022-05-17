#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main(){
	int *arr;
	int shmid = shmget((key_t)2345,0,0666|IPC_EXCL);
	printf("Key of shared memory is %d\n",shmid);
	arr = shmat(shmid, NULL, 0);
	int j=0;
	while(arr[j]!=-1){
        printf("%d  ", arr[j] );
        j+=1;
	}
	printf("\n");
}