#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>
int main() {
	void *shared_memory;
	int shmid;
	shmid = shmget((key_t)2345, 0, 0666);
	printf("Llave de la memoria compartida: %d\n", shmid);
	shared_memory = shmat(shmid, NULL, 0); // process attached to shared memory segment
	// Eliminar el segmento de memoria
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