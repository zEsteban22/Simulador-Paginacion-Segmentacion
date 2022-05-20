#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>
int main()
{
	int i;
	void *shared_memory;
	int shmid;
	shmid = shmget((key_t)2345, 0, 0666);
	printf("Key of shared memory is %d\n", shmid);
	shared_memory = shmat(shmid, NULL, 0); // process attached to shared memory segment
	char buff[100];
	time_t now = time(NULL);
	strftime(buff, 100, "bitacora del %d-%m-%Y a las %H horas con %M minutos y %S segundos.txt", localtime(&now));
	printf("Resultado del rename: %d\nSe generó la %s\n", rename("bitacora.txt", buff), buff);
	// Eliminar el segmento de memoria
	shmdt(shared_memory);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Memoria Liberada\n");
}