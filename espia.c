#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#define BUFF_LEN 1000
void push(int*arr, int pid){
	for (int i=0; i < BUFF_LEN; i++)
		if (arr[i] == 0){
			arr[i] = pid;
			break;
		}
}
void pop(int*arr, int pid){
	for (int i=0; i < BUFF_LEN && arr[i] != 0; i++)
		if (arr[i] == pid){
			i--;
			while (++i < BUFF_LEN - 1)
				arr[i] = arr[i + 1];
			break;
		}
}
void leer_bitacora(){
	char* registro = NULL;
    size_t len = 0;
    ssize_t read;
	int procesosEnEspera[BUFF_LEN] = {0};
	int procesosBuscando[BUFF_LEN] = {0};
	int procesosDormidos[BUFF_LEN] = {0};
	int procesosTerminados[BUFF_LEN] = {0};
	int procesosMuertos[BUFF_LEN] = {0};
	FILE* fptr = fopen("bitacora.txt", "r");
	getline(&registro, &len, fptr); //Se ignora la primera línea.
	while ((read = getline(&registro, &len, fptr)) != -1) {
		char*last=registro+30;
		int pid = (int) strtol(registro + 27, &last, 10);
        switch (registro[31]) {
			case 's'://Se empezó a ejecutar -> sacar de en búsqueda y meter a dormidos
				pop(procesosBuscando,pid);
				push(procesosDormidos,pid);
				break;
			case 'b'://Busca memoria -> sacar de en espera y meter a buscando
				pop(procesosEnEspera,pid);
				push(procesosBuscando,pid);
				break;
			case 'e'://Espera para buscar -> meter a en espera
				push(procesosEnEspera,pid);
				break;
			case 'm'://Murió	-> sacar de buscando y meter en muertos
				pop(procesosBuscando,pid);
				push(procesosMuertos,pid);
				break;
			case 't'://Terminó con éxito -> sacar de dormidos y meter en terminados
				pop(procesosDormidos,pid);
				push(procesosTerminados,pid);
				break;
			default:
				exit(-1);
		}
    }
	fclose(fptr);
	if (procesosEnEspera[0] == 0)
		printf("No hay procesos en espera.\n");
	else{
		printf("Procesos en espera: ");
		for (int i=0; i < BUFF_LEN && procesosEnEspera[i] != 0; i++){
			printf("%d", procesosEnEspera[i]);
			if (i + 1 < BUFF_LEN && procesosEnEspera[i+1] != 0)
				printf(", ");
			else
				printf("\n");
		}
	}
	if (procesosBuscando[0] == 0)
		printf("No hay procesos buscando memoria.\n");
	else{
		printf("Procesos en búsqueda de memoria: ");
		for (int i=0; i < BUFF_LEN && procesosBuscando[i] != 0; i++){
			printf("%d", procesosBuscando[i]);
			if (i + 1 < BUFF_LEN && procesosBuscando[i+1] != 0)
				printf(", ");
			else
				printf("\n");
		}
	}
	if (procesosMuertos[0] == 0)
		printf("No hay procesos muertos.\n");
	else{
		printf("Procesos muertos: ");
		for (int i=0; i < BUFF_LEN && procesosMuertos[i] != 0; i++){
			printf("%d", procesosMuertos[i]);
			if (i + 1 < BUFF_LEN && procesosMuertos[i+1] != 0)
				printf(", ");
			else
				printf("\n");
		}
	}
	if (procesosDormidos[0] == 0)
		printf("No hay procesos en ejecución.\n");
	else{
		printf("Procesos en ejecución actualmente: ");
		for (int i=0; i < BUFF_LEN && procesosDormidos[i] != 0; i++){
			printf("%d", procesosDormidos[i]);
			if (i + 1 < BUFF_LEN && procesosDormidos[i+1] != 0)
				printf(", ");
			else
				printf("\n");
		}
	}
	if (procesosTerminados[0] == 0)
		printf("No hay procesos que hayan terminado su ejecución.\n");
	else{
		printf("Procesos que han salido de la simulación: ");
		for (int i=0; i < BUFF_LEN && procesosTerminados[i] != 0; i++){
			printf("%d", procesosTerminados[i]);
			if (i + 1 < BUFF_LEN && procesosTerminados[i+1] != 0)
				printf(", ");
			else
				printf("\n");
		}
	}
}
void mostrar_memoria(){
	int *arr;
	int shmid = shmget((key_t)2345,0,0666|IPC_EXCL);
	arr = shmat(shmid, NULL, 0);
	int j=0;
	while(arr[j]!=-1){
        printf("%d  ", arr[j] );
        j+=1;
	}
	printf("\n");
}

int main(){
	char r = '\0';
	while(r != 's' && r != 'S'){
		printf("¿Desea ver el estado de la (M)emoria, ver el estado de los (P)rocesos o (S)alir?\n> ");
		scanf("%c",&r);
		if (r != 's' && r != 'S' && r != 'm' && r != 'M' && r != 'p' && r != 'P') 
			printf("Por favor escoja una opción válida, ingrese alguno de los caracteres puestos entre paréntesis.\n");
		else {
			if (r == 'p' || r == 'P'){
				leer_bitacora();
			} else if (r == 'm' || r == 'M'){
				mostrar_memoria();
			} else {
				printf("Adios.\n");
			}
		}
	}

}
