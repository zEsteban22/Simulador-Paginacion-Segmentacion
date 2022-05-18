# Simulador-Paginacion-Segmentacion
#### María José Cortez - #
#### Esteban Cruz López - 2018104794
#### Luis Venegas Leiva - 2019079322

## Introducción
Este proyecto se realizó como parte del curso de Principios de Sistemas Operativos de la carrera de Ingeniería en Computación en el Instituto Tecnológico de Costa Rica en el primer semestre de 2022 con la profesora Erika Marín Shumann.
Se trata de un simulador de paginación o segmentación, según sea inicializado el simulador. Para esto, como ya se indicó, se requiere la implementación de un programa inicializador que solicite el espacio compartido al sistema operativo (Linux) para que el proceso que simula la creación de procesos que van a requerir ser ejecutados por cierto tiempo, así como un determinado tamaño en memoria y la especificación del tamaño de sus segmentos si es que el simulador fue iniciado en modo segmentación. También se requiere un programa 'espía' para la observación del estado del simulador y finalmente un programa dedicado a finiquitar el compartimiento de memoria.

## Desarrollo
Según el enunciado del proyecto será implementado en C en Linux, utilizando las bibliotecas: sys/mman.h, sys/stat.h y fcntl.h, así como la opción -lrt al momento de compilación.

### Estrategia de solución

## Análisis de resultados

## Lecciones aprendidas

## Pruebas

## mmap vs shmget
https://stackoverflow.com/questions/21311080/linux-shared-memory-shmget-vs-mmap

## Manual de usuario+
La solución está planteada para ejecutarse en un ambiente Linux, para compilar en C mediante el compilador gcc.
Primeramente, para la compilación de los 4 programas que componen este proyecto se cuenta con un archivo makefile, por lo que, para realizar la compilación se debe ejecutar el comando 'make'.

Una vez compilados todos los programas, se debe realizar la ejecución del archivo llamado 'inicializador', el cuál se encarga de realizar la asignación de la memoria compartida que se utilizará.

Seguidamente se debe ejecutar el archivo 'productor', en el que el usuario debe seleccionar el tipo de algoritmo que desea utilizar durante la ejecución, esta ventana se debe mantener activa siempre, ya que es la encargada de generar la simulación de procesos de forma constante.

Si se desea conocer los detalles de la simulación, se debe ejecutar el archivo 'espia', el cuál muestra al usuario todos los datos correspondientes a esta.
Cuando se necesite finaliazar la simulación se debe ejecutar el archivo 'finalizador', que es el encargado de detener la simulación y cerrar las instancias de memoria compartida.

## Bitácora de trabajo
7 de mayo: Reunión inicial con todos los integrantes del grupo para acordar el método de trabajo general. Duración 1 hora.

Del 8 al 14 de mayo se trabajó individualmente en una base para cada uno de los programas.

15 de mayo: Reunión en la que ya se cuenta con una base inicial de los 4 programas y se analizan la estructura final que tendrá el programa productor. Duración 1 hora.
16 de mayo: Se realizó parte del algoritmo de paginación.

17 de mayo: Nos reunimos para finalizar el desarrollo de la simulación del algorimto de paginación y avanzar con la bitácora de procesos. Duración 2.5 horas


## Bibliografía
