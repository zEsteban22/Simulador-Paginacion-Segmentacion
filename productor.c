#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

sem_t semaforoProcesos;
  
void* thread(void* arg){
    int i = *(int*)arg;

	//wait
    sem_wait(&semaforoProcesos);
    printf("\nEntra proceso %i\n",i);
    int duracionProceso = rand() % (35 - 15 + 1) + 15; //(60 - 20 + 1) + 20;
    int cantPaginas = rand() % (10 - 1 + 1) + 1;
    printf("Duracion del sleep: %i\n",duracionProceso );
  	printf("Cantidad de paginas: %i\n",cantPaginas );


    //critical section
  	int *arr;
	int shmid = shmget((key_t)2345,0,0666|IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

    size_t act = 0;
	int pagLibres = 0;

	while (arr[act]!=-1 && cantPaginas>pagLibres){
		if(arr[act] == 0){
			pagLibres+=1;
		}
    	act++;
	}
	printf("Paginas libres:%i\n", pagLibres);
	act=0;
	if (pagLibres==cantPaginas){
		while (pagLibres!=0) {
			if(arr[act] == 0){
				arr[act]=i;
				pagLibres-=1;
			}
    		act++;
		}	
	}else{
		printf("Paginas insuficientes\n");
		sem_post(&semaforoProcesos);
		pthread_exit(NULL);
	}
	int j=0;
	while(arr[j]!=-1){
        printf("%d  ", arr[j] );
        j+=1;
	}
	printf("\n");


    //signal
    printf("Proceso %i sale y hace signal...\n",i);
    sem_post(&semaforoProcesos);

    //Se ejecuta el proceso
    sleep(duracionProceso);

    //wait
    sem_wait(&semaforoProcesos);
    printf("\nEntra proceso %i\n",i);
    //critical section
	shmid = shmget((key_t)2345,0,0666|IPC_EXCL);
	arr = shmat(shmid, NULL, 0);

    act=0;
	while (pagLibres<cantPaginas) {
		if(arr[act] == i){
			arr[act]=0;
			pagLibres+=1;
		}
		act++;
	}	
	j=0;
	while(arr[j]!=-1){
        printf("%d  ", arr[j] );
        j+=1;
	}
	printf("\n");

    //signal
    printf("Proceso %i Libera Memoria y hace signal\n",i);
    sem_post(&semaforoProcesos);

    pthread_exit(NULL);
}

void generarProcesos(){
	pthread_t threads[50];
	int i = 0;
	while (1){
		i += 1;

		int espera = rand() % (25 - 5 + 1) + 5;//(60 - 30 + 1) + 30;
		printf("\nProceso numero %i generado\n", i);
		printf("Tiempo entre generacion: %i\n",espera);


		int ret = pthread_create(&threads[i], NULL, &thread, (void*)&i);
		if (ret != 0)
		{
			printf("Error al crear el thread");
		}

		sleep(espera);
	}
	pthread_exit(NULL);
}

int main(){
	sem_init(&semaforoProcesos, 0, 1);

	generarProcesos();
	/*
	int i;
	for(i=0; i<5; i++) 
        printf("%d\n", arr[i] );	*/

	sem_destroy(&semaforoProcesos);
    return 0;
}
