# Simulador-Paginación-Segmentación

#### María José Cortés - 2018138674

#### Esteban Cruz López - 2018104794

#### Luis Venegas Leiva - 2019079322

## Introducción

Este proyecto se realizó como parte del curso de Principios de Sistemas Operativos de la carrera de Ingeniería en Computación en el Instituto Tecnológico de Costa Rica en el primer semestre de 2022 con la profesora Erika Marín Shumann.

Se trata de un simulador de paginación o segmentación, según sea inicializado el simulador. Para esto, según fue mencionado, se requiere la implementación de un programa inicializador que solicite el espacio compartido al sistema operativo (Linux) para que el programa que simula la creación de procesos que van a requerir ser ejecutados por cierto tiempo, así como un determinado tamaño en memoria y la especificación del tamaño de sus segmentos si es que el simulador fue iniciado en modo segmentación.

También se requiere un programa 'espía' para la observación del estado del simulador y finalmente un programa dedicado a finiquitar el compartimiento de memoria.


## Desarrollo

Según el enunciado del proyecto será implementado en C en Linux, utilizando las bibliotecas: sys/mman.h, sys/stat.h y fcntl.h, así como la opción -lrt al momento de compilación.


### Estrategia de solución


## Análisis de resultados


## Lecciones aprendidas

Durante el desarrollo de este proyecto pudimos aprender los distintos métodos para manejar la memoria compartida en el lenguaje de programación c, en este caso con shm y mmap, así como los distintos comandos que permiten visualizar todos los segmentos de memoria compartidos en el sistema operativo.

Además también aprendimos a aplicar los conocimientos adquiridos en el curso sobre semáforos y comprendimos la forma en la que estos se crea, modifican y destruyen en el lenguaje de programación c.

Este proyecto también nos ayudó a reforzar, aplicar e implementar en un lenguaje de programación una simulación los algoritmos de paginación y segmentación.


## Pruebas


## mmap vs shmget

La principal diferencia entre mmap y shmget radica en que mmap es un poco más restrictiva, pero también es más simple o fácil de usar, shmget es un método más antiguo, por lo que tiene un soporte más completo.

Mmap mapea el contenido de un archivo a una sección de memoria y este archivo puede ser modificado y leído cuando se lee o modifica esta sección de memoria, y los procesos pueden acceder al archivo de la forma que acceden a memoria, sin llamar las instrucciones del sistema (read, write).

Mientras que shm mapea directamente el espacio de la memoria virtual del proceso a la memoria física.

Por lo tanto, mmap es más simple de usar y más conveniente que shm, por lo que la mayoria de personas prefieren utilizar mmap.

Otra ventaja de mmap es que cuando la computadora se reinicia, mmap no se perderá, ya que guarda el archivo en disco, y este archivo también guarda la imagen de sincronización del sistema operativo.


## Manual de usuario

La solución está planteada para ejecutarse en un ambiente Linux, para compilar en C mediante el compilador gcc.
Primeramente, para la compilación de los 4 programas que componen este proyecto se cuenta con un archivo makefile, por lo que, para realizar la compilación se debe ejecutar el comando 'make'.

Una vez compilados todos los programas, se debe realizar la ejecución del archivo llamado 'inicializador', el cuál se encarga de realizar la asignación de la memoria compartida que se utilizará. Este programa pedirá al usuario elegir el tipo de algoritmo que desea implementar para la simulación, además de controlar la cantidad de espacios que se utilizarán como espacios de memoria durante la simulación.

Seguidamente se debe ejecutar el archivo 'productor', esta ventana se debe mantener activa siempre, ya que es la encargada de generar la simulación de procesos de forma constante, además muestra información de los procesos que son creados y el manejo de memoria compartida de estos.

Si se desea conocer los detalles de la simulación, se debe ejecutar el archivo 'espia', el cuál muestra al usuario todos los datos correspondientes a esta.
Cuando se necesite finalizar la simulación se debe ejecutar el archivo 'finalizador', que es el encargado de detener la simulación y cerrar las instancias de memoria compartida.

Cuando se desee detener la simulación se debe ejecutar el programa "finalizador", que se encarga de devolver los segmentos de memoria compartida y cerrar la bitácora.


## Bitácora de trabajo

7 de mayo: Reunión inicial con todos los integrantes del grupo para acordar el método de trabajo general. Duración 1 hora.

Del 8 al 14 de mayo se trabajó individualmente en una base para cada uno de los programas.

15 de mayo: Reunión en la que ya se cuenta con una base inicial de los 4 programas y se analizan la estructura final que tendrá el programa productor. Duración 1 hora.
16 de mayo: Se realizó parte del algoritmo de paginación.

17 de mayo: Nos reunimos para finalizar el desarrollo de la simulación del algoritmo de paginación y avanzar con la bitácora de procesos. Duración 2.5 horas

18 de mayo: Se trabajó de forma asincrónica en la elaboración de la bitácora. Duración 4 horas

19 de mayo: Se trabajó de forma asincrónica en desarrollo del algoritmo de segmentación. Duración 3 horas

20-21 de mayo: Se diseña el programa espía con todas sus funcionalidades (ver estado de memoria e información de procesos). Duración 4 horas


## Bibliografía

ExchangeStatus(2014). Linux shared memory: shmget() vs mmap()?. Extraído de: https://exchangetuts.com/linux-shared-memory-shmget-vs-mmap-1639552984343707

Programmer Group(2021). Shared memory performance comparison of mmap, shm and MappedByteBuffer. Extraído de: https://programmer.group/shared-memory-performance-comparison-of-mmap-shm-and-mappedbytebuffer.html
