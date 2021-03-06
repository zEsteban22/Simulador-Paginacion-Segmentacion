#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <locale.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
sem_t * sem;
sem_t * semBit;

sem_t semaforoProcesos;
sem_t sB; // Este es el semaforo para escribir en bitacora
char* bitacora = "bitacora.txt";
time_t inicio;
bool esPaginacion;

void manejar_interrupcion(int _) {
	sem_wait(semBit);
	sem_destroy(sem);
	sem_destroy(semBit);
	exit(0);
}

void registrar(char* texto) {
	sem_wait(semBit);
	time_t t;
	time(&t);
	char registro[200];
	// Se hace el registro con el calculo de diferencia de tiempo desde que inició el programa
	sprintf(registro, "%04d: %s", (int)(t - inicio) % 10000, texto);
	FILE* fptr = fopen(bitacora, "a");
	fputs(registro, fptr);
	fclose(fptr);
	sem_post(semBit);
}
void registrar_buscar(int pid) {
	char registro[69];
	sprintf(registro, "El proceso con pid = %03d busca su campo en memoria.\n", pid);
	registrar(registro);
}
void registrar_espera(int pid) {
	char registro[70];
	sprintf(registro, "El proceso con pid = %03d espera para buscar campo en memoria.\n", pid);
	registrar(registro);
}
void registrar_muerte(int pid) {
	char registro[74];
	sprintf(registro, "El proceso con pid = %03d murió al no encontrar campo en memoria.\n", pid);
	registrar(registro);
}
void registrar_inicio(int pid, char* campos) {
	char registro[200];
	sprintf(registro, "El proceso con pid = %03d se empezó a ejecutar habiendo encontrado estos campos %s.\n", pid, campos);
	registrar(registro);
}
void registrar_salida(int pid) {
	char registro[80];
	sprintf(registro, "El proceso con pid = %03d terminó de ejecutarse y salió de la memoria.\n", pid);
	registrar(registro);
}

void* threadPaginacion(void* arg) {
	int i = *(int*)arg;
	printf("\nEmpieza a crearse el proceso %i\n", i);
	int duracionProceso = rand() % (60 - 20 + 1) + 20;
	const int cantPaginas = rand() % (10 - 1 + 1) + 1;
	printf("Duracion del sleep: %i\n", duracionProceso);
	printf("Cantidad de paginas: %i\n", cantPaginas);
	
	// inicio región crítica
	if (sem_trywait(sem) != 0){
		registrar_espera(i);
		sem_wait(sem);
	}
	
	registrar_buscar(i);

	int* arr;
	int shmid = shmget((key_t)2345, 0, 0666 | IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

	size_t act = 0;
	int pagLibres = 0;

	while (arr[act] != -1 && cantPaginas > pagLibres) {
		if (arr[act] == 0)
			pagLibres += 1;
		act++;
	}
	printf("Paginas libres:%i\n", pagLibres);
	act = 0;
	char paginasAsignadas[20];
	if (pagLibres == cantPaginas) {
		while (pagLibres != 0) {
			if (arr[act] == 0) {
				arr[act] = i;
				pagLibres -= 1;
				char s[4];
				sprintf(s, "%02ld", act);
				strcat(paginasAsignadas, s);
				if (pagLibres > 0)
					strcat(paginasAsignadas, ", ");
			}
			act++;
		}
	}
	else {
		registrar_muerte(i);
		sem_post(sem);
		pthread_exit(NULL);
	}
	sem_post(sem);
	registrar_inicio(i, paginasAsignadas);

	sleep(duracionProceso);

	sem_wait(sem);
	shmid = shmget((key_t)2345, 0, 0666 | IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

	act = 0;
	while (pagLibres < cantPaginas) {
		if (arr[act] == i) {
			arr[act] = 0;
			pagLibres += 1;
		}
		act++;
	}

	registrar_salida(i);

	// signal
	printf("Proceso %i libera memoria y sale del contexto\n", i);
	sem_post(sem);

	pthread_exit(NULL);
}

void* threadSegmentacion(void* arg) {
	int i = *(int*)arg;
	printf("\nEmpieza a crearse el proceso %i\n", i);
	int duracionProceso = rand() % (60 - 20 + 1) + 20;
	const int cantSegmentos = rand() % (5 - 1 + 1) + 1;
	int segmentSizes[cantSegmentos];
	for (int j = 0; j < cantSegmentos; j++)
		segmentSizes[j] = rand() % (3 - 1 + 1) + 1;
	printf("Duracion del sleep: %i\n", duracionProceso);
	printf("Cantidad de segmentos: %i\n", cantSegmentos);
	int cantTotal;
	for (int i = 0; i < cantSegmentos; i += 1) {
		printf("%i  ", segmentSizes[i]);
	}
	printf("\n");

	// inicio región crítica
	if (sem_trywait(sem) != 0){
		registrar_espera(i);
		sem_wait(sem);
	}
	
	registrar_buscar(i);

	int* arr;
	int shmid = shmget((key_t)2345, 0, 0666 | IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

	size_t act = 0;
	size_t segmentoActual = 0;
	int pagLibres = 0;
	char paginasAsignadas[20];
	while (arr[act] != -1 && segmentoActual != cantSegmentos) {
		if (arr[act] == 0) {
			pagLibres += 1;
			if (segmentSizes[segmentoActual] == pagLibres)  {
				segmentoActual += 1;
				while (pagLibres != 0) {
					pagLibres -= 1;
					arr[act - pagLibres] = i;
					char s[4];
					sprintf(s, "%02ld", act - pagLibres);
					strcat(paginasAsignadas, s);
					strcat(paginasAsignadas, ", ");
				}
			}
		}
		act += 1;
	}

	act = 0;
	if (segmentoActual != cantSegmentos) {
		while (arr[act] != -1) {
			if (arr[act] == i) {
				arr[act] = 0;
			}
			act += 1;
		}
		registrar_muerte(i);
		printf("Proceso %i muere\n", i);
		sem_post(sem);
		pthread_exit(NULL);
	}
	sem_post(sem);

	registrar_inicio(i, paginasAsignadas);

	sleep(duracionProceso);

	sem_wait(sem);
	shmid = shmget((key_t)2345, 0, 0666 | IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

	act = 0;
	while (arr[act] != -1) {
		if (arr[act] == i)
			arr[act] = 0;
		act += 1;
	}

	registrar_salida(i);

	// signal
	printf("\nProceso %i libera memoria y sale del contexto\n\n", i);
	sem_post(sem);

	pthread_exit(NULL);
}

void generarProcesos() {
	pthread_t threads[50];
	int i = 0;
	while (1) {
		i += 1;
		int espera = rand() % (60 - 30 + 1) + 30;
		printf("\nProceso numero %i generado\n", i);
		printf("Tiempo entre generación: %i\n", espera);
		int ret = pthread_create(&threads[i], NULL, esPaginacion ? &threadPaginacion : &threadSegmentacion, (void*)&i);
		if (ret != 0)
			printf("Error al crear el thread");
		sleep(espera);
	}
	pthread_exit(NULL);
}

int main() {
	sem=sem_open("/semaforoMemoria",  O_RDWR); 
	semBit=sem_open("/semaforoBitacora",  O_RDWR); 

	signal(SIGINT, manejar_interrupcion);
	setlocale(LC_ALL, "");
	time(&inicio);
	char registro[33];
	FILE* fptr = fopen(bitacora, "r");
	fgets(registro, 33, fptr);
	fclose(fptr);
	esPaginacion = registro[31] == 'p';
	printf("¿Es paginación?\n%s.\n", esPaginacion ? "Sí" : "No");
	generarProcesos();
}
