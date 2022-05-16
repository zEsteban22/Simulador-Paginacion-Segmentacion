#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main(){
	void *shared_memory;
	int shmid;
	shmid=shmget((key_t)2345, 0, 0666);
	printf("Key of shared memory is %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
	printf("Process attached at %p\n",shared_memory);
	
	printf("%c\n",*((char*)shared_memory+5));
	printf("Data read from shared memory is : %s\n",(char *)shared_memory);

}