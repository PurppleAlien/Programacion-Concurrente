# Programación Concurrente

**Autor:** Soria Rodriguez Juan Antonio G.  

Repositorio de prácticas de la materia Programación Concurrente. Todos los programas están escritos en C y compilados con `gcc`.

## Resumen de prácticas

| Carpeta | Tema | Técnica |
|---|---|---|
| [Practica1/](Practica1/README.md) | Calculadora de sistemas de numeración (binario, octal, hex) | Aritmética bit a bit, listas ligadas |
| [Practica 2/](Practica%202/README.md) | Métodos de ordenamiento con comparación de tiempos | Burbuja, Inserción, Selección, MergeSort |
| [Practica 3 concurrente/](Practica%203%20concurrente/README.md) | Algoritmo genético para armaduras planas | AG: inicialización, evaluación, cruce, mutación |
| [Pracatica4_Concurrente/](Pracatica4_Concurrente/README.md) | Árbol binario de procesos | `fork()`, cola BFS vs recursión DFS |
| [Practica 5/](Practica%205/README.md) | Ordenamiento secuencial vs concurrente | `fork()` con 4 procesos hijos en paralelo |
| [Practica 6/](Practica%206/README.md) | Coloración de grafos desde archivo | AG con lectura de matriz de adyacencia |
| [Practica7/](Practica7/README.md) | Coloración de grafos 4×4 | AG con matriz hardcoded, criterio de parada óptimo |

## Compilación general

Todos los programas se compilan con:
```bash
gcc -o <ejecutable> <archivo>.c
```

Para programas que usan MPI (Práctica 6):
```bash
mpicc -o <ejecutable> <archivo>.c
mpirun -np <num_procesos> ./<ejecutable> <args>
```

## Dependencias

- `gcc` — compilador C
- `make` (opcional)
- `openmpi-bin` / `libopenmpi-dev` — solo para la versión MPI de Práctica 6

```bash
# Instalar dependencias en Debian/Ubuntu/Kali
sudo apt install gcc openmpi-bin libopenmpi-dev
```
