# Simulador-Paginacion-Segmentacion
#### María José Cortez - #
#### Esteban Cruz López - 2018104794
#### Luis Venegas Leiva - 2019079322
## Introducción
Este proyecto se realizó como parte del curso de Principios de Sistemas Operativos de la carrera de Ingeniería en Computación en el Instituto Tecnológico de Costa Rica en el primer semestre de 2022 con la profesora Erika Marín Shumann.
Se trata de un simulador de paginación o segmentación, según sea inicializado el simulador. Para esto, como ya se indicó, se requiere la implementación de un programa inicializador que solicite el espacio compartido al sistema operativo (Linux) para que el proceso que simula la creación de procesos que van a requerir ser ejecutados por cierto tiempo, así como un determinado tamaño en memoria y la especificación del tamaño de sus segmentos si es que el simulador fue iniciado en modo segmentación. También se requiere un programa 'espía' para la observación del estado del simulador y finalmente un programa dedicado a finiquitar el compartimiento de memoria.
## Desarrollo
Según el enunciado del proyecto será implementado en C en Linux, utilizando las bibliotecas: sys/mman.h, sys/stat.h y fcntl.h, así como la opción -lrt al momento de compilación.
