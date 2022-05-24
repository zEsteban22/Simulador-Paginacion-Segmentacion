#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t * sem;
sem_t * semBit;
int main() {
	sem=sem_open("/semaforoMemoria",  O_RDWR); 
	semBit=sem_open("/semaforoBitacora",  O_RDWR); 
	sem_unlink("/semaforoMemoria"); 
	sem_unlink("/semaforoBitacora"); 
	sem_close(sem);
	sem_close(semBit);
	void *shared_memory;
	int shmid;
	shmid = shmget((key_t)2345, 0, 0666);
	printf("Llave de la memoria compartida: %d\n", shmid);
	shared_memory = shmat(shmid, NULL, 0);
	shmdt(shared_memory);
	shmctl(shmid, IPC_RMID, NULL);
	if (shmid >= 0)
		printf("Memoria liberada.\n");
	char buff[100];
	time_t now = time(NULL);
	strftime(buff, 100, "bitacora del %d-%m-%Y a las %H horas con %M minutos y %S segundos.txt", localtime(&now));
	int r = rename("bitacora.txt", buff);
	printf("Resultado del rename: %d\n", r);
	if (r == 0) 
		printf("Se generó la %s\n", buff);
}