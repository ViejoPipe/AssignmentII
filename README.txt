Algoritmos de Planificación de Procesos

Esta asignación implementa 4 algoritmos de planificación de procesos:
1. FCFS (First Come, First Served)
2. SJF (Shortest Job First)
3. Round Robin
4. Shortest Time of Completion First

Cada algoritmo utiliza un archivo de texto como entrada. Dentro de la carpeta de cada algoritmo encontrarás 3 archivos de ejemplo.

------------------------------------------------------------
Formato de Entrada
------------------------------------------------------------

1. FCFS y SJF
Cada línea representa un proceso con el siguiente formato:
<nombre_proceso> <arrival_time> <burst_time>

Ejemplo:
P1 0 5
P2 2 3
P3 4 1

------------------------------------------------------------

2. Round Robin
El archivo debe seguir esta estructura:
- Primera línea: número total de procesos
- Segunda línea: el quantum
- Siguientes líneas: arrival time y burst time de cada proceso

Ejemplo:
3
2
0 5
1 3
2 8

------------------------------------------------------------

3. Shortest Time of Completion First
El archivo debe seguir esta estructura:
- Primera línea: número de procesos
- Siguientes líneas: arrival time y burst time de cada proceso

Ejemplo:
3
0 5
2 3
4 1

------------------------------------------------------------
Ejecución
------------------------------------------------------------
Una vez tengas tu archivo, compila el programa y ejecútalo. El programa te pedirá el nombre del archivo y luego mostrará los tiempos de cada proceso: completion time, turnaround time, waiting time y response time.