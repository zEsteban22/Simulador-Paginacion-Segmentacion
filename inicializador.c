#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main(){
	void *shared_memory;
	char buff[100];
	int shmid;

	int *arr;
	int tam=20;

	shmid = shmget((key_t)2345,sizeof(int)*(tam+1),0666|IPC_CREAT);
	arr = (int *)shmat(shmid, NULL, 0);
	arr = (int *)shmat(shmid, NULL, 0);
	int i;
	for(i=0; i<tam; i++)
    	arr[i] = 0;
    arr[i+1] = -1;

	for(i=0; i<tam; i++)
    	printf("%d\n", arr[i]);

    /*
	shmid=shmget((key_t)2345, 18, 0666|IPC_CREAT); //creates shared memory segment with key 2345, having size 1024 bytes. IPC_CREAT is used to create the shared segment if it does not exist. 0666 are the permisions on the shared segment
	printf("Key of shared memory is %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
	//printf("Process attached at %p\n",shared_memory); //this prints the address where the segment is attached with this process

	strcpy(buff,"000000000000000000000000000000");
	strcpy(shared_memory,buff); //data written to shared memory*/
}