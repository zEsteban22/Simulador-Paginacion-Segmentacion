#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
	void *shared_memory;
	char buff[100];
	int shmid;

	int *arr;
	int tam = 20;

	shmid = shmget((key_t)2345, sizeof(int) * (tam + 1), 0666 | IPC_CREAT);
	arr = (int *)shmat(shmid, NULL, 0);
	arr = (int *)shmat(shmid, NULL, 0);
	int i;
	for (i = 0; i < tam; i++)
		arr[i] = 0;
	arr[i + 1] = -1;

	for (i = 0; i < tam; i++)
		printf("%d ", arr[i]);
	char r = '\0';
	while (r != 'p' && r != 'P' && r != 's' && r != 'S')
	{
		printf("\nEscoja por favor el método de manejo de memoria: P - paginación o S - segmentación\n>");
		scanf("%c", &r);
		if (r != 'p' && r != 'P' && r != 's' && r != 'S')
			printf("\nPor favor intente de nuevo.");
	}
	char texto[100];
	if (r == 'p' || r == 'P')
		sprintf(texto, "Se ha escogido el algoritmo de paginación.\n");
	else
		sprintf(texto, "Se ha escogido el algoritmo de segmentación.\n");
	printf(texto);
	FILE *fptr = fopen("bitacora.txt", "w");
	fputs(texto, fptr);
	fclose(fptr);
}