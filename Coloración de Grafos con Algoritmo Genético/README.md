# Práctica 6 — Coloración de Grafos con Algoritmo Genético

**Alumno:** Soria Rodriguez Juan Antonio G.  
**Matrícula:** 2203041232  
**Materia:** Programación Concurrente

## Descripción

Resuelve el problema de **coloración de mapas/grafos** usando un algoritmo genético. Lee la matriz de adyacencia del grafo desde un archivo `.txt` y encuentra la asignación de colores que minimiza conflictos (regiones adyacentes con el mismo color).

### Operaciones del algoritmo genético
1. **Lectura del grafo** — matriz de adyacencia desde archivo.
2. **Inicialización** — población aleatoria de asignaciones de colores.
3. **Fitness** — cuenta el número de conflictos (aristas con mismo color en ambos extremos).
4. **Cruce** — cruce de un punto en la mitad del cromosoma.
5. **Mutación** — cambio aleatorio de un gen.
6. **Selección del mejor** — individuo con menor número de conflictos.

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `Practica6.c` | Programa principal del algoritmo genético para coloración |
| `MaterialPractica6/Genetico.c` | Variante del algoritmo genético |
| `MaterialPractica6/GENETICOII.c` | Segunda variante |
| `MaterialPractica6/VisualizacionGrafos.c` | Herramienta de visualización de grafos |
| `MaterialPractica6/mpi.c` | Versión con MPI (requiere `mpicc`) |
| `MaterialPractica6/graf*.txt` | Archivos de grafos de distintos tamaños |

### Archivos de grafos disponibles

| Archivo | Tamaño |
|---|---|
| `graf4x4.txt` | 4 × 4 |
| `graf10x10.txt` | 10 × 10 |
| `graf14x15.txt` | 14 × 15 |
| `graf20x20.txt` | 20 × 20 |
| `graf30x20.txt` | 30 × 20 |
| `graf50x50.txt` | 50 × 50 |
| `graf80x80.txt` | 80 × 80 |
| `graf100x100.txt` | 100 × 100 |

## Compilación y ejecución

```bash
cd "Practica 6"

# Programa principal
gcc -o Practica6 Practica6.c
./Practica6 MaterialPractica6/graf10x10.txt
```

El programa recibe el **archivo del grafo como argumento**:
```
./Practica6 <archivo_grafo>
```

## Uso

```
Introduzca el numero de colores: 4
Introduzca el tamaño de su POBLACION: 20
```

### Salida
```
Población inicial:
2 0 3 1 0 2 ...

Aplicando operaciones genéticas:
Iteración 0, Fitness: 5
Iteración 1, Fitness: 3
...
El mejor óptimo después de las operaciones genéticas tiene el fitness = 0
CO[N]:
0 1 2 3 1 0 ...
```

Un **fitness de 0** indica que se encontró una coloración válida (sin conflictos).

## Notas
- Ejecuta **500 iteraciones fijas** (modificable en `geneticAlgorithm(500)`).
- `MAX_POPULATION = 100`, `MAX_COLORS = 10`, `MAX_REGIONS = 1000`.
- La versión MPI requiere: `mpicc -o mpi MaterialPractica6/mpi.c && mpirun -np 4 ./mpi <archivo>`.
