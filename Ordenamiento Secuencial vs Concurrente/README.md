# Ordenamiento Secuencial vs Concurrente

**Autor:** Soria Rodriguez Juan Antonio G.  
**Materia:** Programación Concurrente

## Descripción

Compara el rendimiento de cuatro algoritmos de ordenamiento ejecutados de forma **secuencial** contra su ejecución **concurrente** usando procesos hijos (`fork()`). Cada algoritmo opera sobre una copia independiente del mismo arreglo aleatorio.

### Algoritmos comparados
- Burbuja
- Selección Directa
- Inserción Directa
- Merge Sort

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `Practica5_ASecuencial.c` | Ejecuta los 4 algoritmos uno tras otro y mide el tiempo total |
| `Practica5_AConcurrente.c` | Lanza 4 procesos hijos en paralelo, cada uno ejecuta un algoritmo |
| `Practica5_B_SECUENCIAL.c` | Variante secuencial (parte B) |
| `Practica3_B_Concurrente.c` | Variante concurrente (parte B) |

## Compilación y ejecución

```bash
# Versión secuencial
gcc -o secuencial Practica5_ASecuencial.c
./secuencial

# Versión concurrente
gcc -o concurrente Practica5_AConcurrente.c
./concurrente
```

## Uso

Ambas versiones solicitan los mismos datos:
```
Dame el tamano de los elementos del arreglo: 10000
Quieres desplegar los elementos del arreglo? 1-> si, 0-> no: 0
```

### Salida secuencial
```
ORDENAMIENTO SECUENCIAL
Metodo Burbuja: 0.42 segundos
Metodo Insercion Directa: 0.18 segundos
Metodo Seleccion Directa: 0.21 segundos
Metodo MergeSort: 0.00 segundos
Tiempo total de ejecucion del programa: 0.00 segundos
```

### Salida concurrente
```
ORDENAMIENTO CONCURRENTE
Metodo Burbuja: 0.42 segundos
Metodo Seleccion Directa: 0.21 segundos
Metodo Insercion Directa: 0.18 segundos
Metodo MergeSort: 0.00 segundos
```
> En la versión concurrente el orden de las líneas puede variar porque los procesos corren en paralelo.

## Notas
- La versión concurrente crea **4 procesos hijos** simultáneamente con `fork()`.
- El proceso maestro espera a todos los hijos con `wait(NULL)` antes de terminar.
- Para arreglos grandes (>100,000 elementos) la diferencia entre secuencial y concurrente es más notable.
