#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

sem_t semaforoProcesos;
  
void* thread(void* arg){
    //wait
    int i = *(int*)arg;

	void *shared_memory;
	char buff[100];
	int shmid;


	/*
	printf("Enter some data to write to shared memory\n");
	read(0,buff,100); //get some input from user
	strcpy(shared_memory,buff); //data written to shared memory
	*/





    sem_wait(&semaforoProcesos);
    printf("\nEntra proceso %i\n",i);
    int duracionProceso = rand() % (35 - 15 + 1) + 15; //(60 - 20 + 1) + 20;
    int cantPaginas = rand() % (10 - 1 + 1) + 1;
    printf("Duracion del sleep: %i\n",duracionProceso );
  	printf("Cantidad de paginas: %i\n",cantPaginas );

    //critical section
    
  	shmid=shmget((key_t)2345, 0, 0666);
	//printf("Key of shared memory is %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
	//printf("Process attached at %p\n",shared_memory);
	printf("Lee lo siguiente: %s\n",(char *)shared_memory);

	char mem[100];
	strcpy(mem,(char *)shared_memory);
	size_t act = 0;
	int pagLibres = 0;
	while (mem[act] != '\0' && cantPaginas>pagLibres) {       /* Stop looping when we reach the null-character. */
		if(mem[act] == '0'){
			pagLibres+=1;
		}
    	act++;
	}
	printf("Paginas libres:%i\n", pagLibres);
	char c=i+'0';
	act=0;
	if (pagLibres==cantPaginas){
		while (pagLibres!=0) {
			if(mem[act] == '0'){
				mem[act]=c;
				pagLibres-=1;
			}
    		act++;
		}	
	}else{
		printf("Paginas insuficientes\n");
		sem_post(&semaforoProcesos);
		pthread_exit(NULL);
	}

	printf("Y escribe esto: %s\n", mem);;
	strcpy(shared_memory,mem); //data written to shared memory




    //signal
    printf("Proceso %i sale y hace signal...\n",i);
    sem_post(&semaforoProcesos);

    //Se ejecuta el proceso
    sleep(duracionProceso);

    //wait
    sem_wait(&semaforoProcesos);

    c=i+'0';
    printf("\nEntra proceso %i\n",i);
    //critical section
  	shmid=shmget((key_t)2345, 0, 0666);
	shared_memory=shmat(shmid,NULL,0);
	printf("Lee lo siguiente: %s\n",(char *)shared_memory);
	strcpy(mem,(char *)shared_memory);

    act=0;
	while (pagLibres<cantPaginas) {
		if(mem[act] == c){
			mem[act]='0';
			pagLibres+=1;
		}
		act++;
	}	

	printf("Y escribe esto: %s\n",mem );
	strcpy(shared_memory,mem); //data written to shared memory

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
	/*
	int i;
	void *shared_memory;
	char buff[100];
	int shmid;
	shmid=shmget((key_t)2345, 0, 0666);
	printf("Key of shared memory is %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
	printf("Process attached at %p\n",shared_memory);
	printf("Data read from shared memory is : %s\n",(char *)shared_memory);
	/*
	printf("Enter some data to write to shared memory\n");
	read(0,buff,100); //get some input from user
	strcpy(shared_memory,buff); //data written to shared memory
	*/

	sem_init(&semaforoProcesos, 0, 1);

	generarProcesos();	

	sem_destroy(&semaforoProcesos);
    return 0;
}
