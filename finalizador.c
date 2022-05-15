#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main(){
	int i;
	void *shared_memory;
	int shmid;
	shmid=shmget((key_t)2345, 0, 0666);
	printf("Key of shared memory is %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment

	//Eliminar el segmento de memoria
	shmdt(shared_memory);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Memoria Liberada\n");
}