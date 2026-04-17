# Práctica 2 — Métodos de Ordenamiento

**Alumno:** Soria Rodriguez Juan Antonio G.  
**Matrícula:** 2203041232  
**Materia:** Programación Concurrente

## Descripción

Implementación y comparación de cuatro algoritmos de ordenamiento sobre arreglos de enteros generados aleatoriamente. Mide y reporta el tiempo de CPU de cada método.

### Algoritmos implementados
- **Burbuja** — O(n²)
- **Inserción Directa** — O(n²)
- **Selección Directa** — O(n²)
- **Merge Sort** — O(n log n)

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `Codigos Practica2/Practica1_A.c` | Programa principal con menú interactivo y comparador de tiempos |
| `Codigos Practica2/Practica1_B.c` | Variante del programa principal (misma funcionalidad) |
| `Metodos de Ordenamiento/burbuja.c` | Algoritmo burbuja standalone |
| `Metodos de Ordenamiento/insercion_Directa.c` | Inserción directa standalone |
| `Metodos de Ordenamiento/seleccion_directa.c` | Selección directa standalone |
| `Metodos de Ordenamiento/merge_sort.c` | Merge sort standalone |

## Compilación y ejecución

### Programa con menú (recomendado)
```bash
cd "Codigos Practica2"
gcc -o Practica1_A Practica1_A.c
./Practica1_A
```

### Métodos individuales
```bash
cd "Metodos de Ordenamiento"
gcc -o burbuja burbuja.c && ./burbuja
gcc -o insercion_Directa insercion_Directa.c && ./insercion_Directa
gcc -o seleccion_directa seleccion_directa.c && ./seleccion_directa
gcc -o merge_sort merge_sort.c && ./merge_sort
```

## Uso

```
Menu de Ordenamiento
1. Ordenar por Burbuja
2. Ordenar por Insercion Directa
3. Ordenar por Seleccion Directa
4. Ordenar por MergeSort Recursivo
5. Comparar tiempos de todos los metodos   ← útil para benchmarks
6. Salir
```

Al seleccionar una opción se pide:
- **Tamaño del arreglo** — se genera aleatoriamente entre 0 y 1000.
- **Mostrar elementos** — `1` para ver el arreglo antes y después de ordenar.

## Notas
- La opción **5** ejecuta los cuatro algoritmos sobre el **mismo arreglo** y compara tiempos.
- Los valores aleatorios se generan en el rango `[0, 1000]` (modificable en `llenarArreglo`).
