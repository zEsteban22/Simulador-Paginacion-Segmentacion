#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t * sem;
sem_t * semBit;
char esNumero(char* str) {
    int j;
    j = strlen(str);
    while(j--) {
        if(str[j] > 47 && str[j] < 58)
            continue;
        return 0;
    }
    return 1;
}
int main() {
	sem_unlink ("/semaforoMemoria"); 
	sem_unlink ("/semaforoBitacora"); 

	sem=sem_open("/semaforoMemoria",  O_CREAT,0666,1);
	semBit=sem_open("/semaforoBitacora",  O_CREAT,0666,1);
	
	sem_wait(sem);
	void *shared_memory;
	char buff[100];
	int shmid;

	int *arr;
	int tam = 0;
	char r[10] = {'\0'};
	while(tam == 0){
		printf("Ingrese la cantidad de unidades espaciales de memoria.\n> ");
		scanf("%s", r);
		if (esNumero(r)) {
			tam = atoi(r);
		}
	}
	shmid = shmget((key_t)2345, sizeof(int) * (tam + 1), 0666 | IPC_CREAT);
	arr = (int *)shmat(shmid, NULL, 0);
	int i;
	for (i = 0; i < tam; i++)
		arr[i] = 0;
	arr[i + 1] = -1;

	for (i = 0; i < tam; i++)
		printf("%d ", arr[i]);
	sem_post(sem);
	sem_close(sem);

	while (r[0] != 'p' && r[0] != 'P' && r[0] != 's' && r[0] != 'S') {
		printf("\nEscoja por favor el método de manejo de memoria: P - paginación o S - segmentación\n> ");
		scanf("%s", r);
		if (r[0] != 'p' && r[0] != 'P' && r[0] != 's' && r[0] != 'S')
			printf("\nPor favor intente de nuevo.");
	}
	char texto[100];
	if (r[0] == 'p' || r[0] == 'P')
		sprintf(texto, "Se ha escogido el algoritmo de paginación.\n");
	else
		sprintf(texto, "Se ha escogido el algoritmo de segmentación.\n");
	printf(texto);
	sem_wait(semBit);
	FILE *fptr = fopen("bitacora.txt", "w");
	fputs(texto, fptr);
	fclose(fptr);
	sem_post(semBit);
	sem_close(semBit);
}