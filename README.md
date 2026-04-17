# Programación Concurrente

**Autor:** Soria Rodriguez Juan Antonio G.  
**Materia:** Programación Concurrente

Repositorio de proyectos de la materia Programación Concurrente. Todos los programas están escritos en C y compilados con `gcc`.

## Proyectos

| Carpeta | Tema | Técnica |
|---|---|---|
| [Calculadora de Sistemas de Numeración](Calculadora%20de%20Sistemas%20de%20Numeración/README.md) | Calculadora de sistemas de numeración (binario, octal, hex) | Aritmética bit a bit, listas ligadas |
| [Métodos de Ordenamiento](M%C3%A9todos%20de%20Ordenamiento/README.md) | Métodos de ordenamiento con comparación de tiempos | Burbuja, Inserción, Selección, MergeSort |
| [Algoritmo Genético para Armaduras Planas](Algoritmo%20Gen%C3%A9tico%20para%20Armaduras%20Planas/README.md) | Algoritmo genético para armaduras planas | AG: inicialización, evaluación, cruce, mutación |
| [Árbol Binario de Procesos](Árbol%20Binario%20de%20Procesos/README.md) | Árbol binario de procesos | `fork()`, cola BFS vs recursión DFS |
| [Ordenamiento Secuencial vs Concurrente](Ordenamiento%20Secuencial%20vs%20Concurrente/README.md) | Ordenamiento secuencial vs concurrente | `fork()` con 4 procesos hijos en paralelo |
| [Coloración de Grafos con Algoritmo Genético](Coloraci%C3%B3n%20de%20Grafos%20con%20Algoritmo%20Gen%C3%A9tico/README.md) | Coloración de grafos desde archivo | AG con lectura de matriz de adyacencia |
| [Coloración de Grafos con Algoritmo Genético (Variante)](Coloraci%C3%B3n%20de%20Grafos%20con%20Algoritmo%20Gen%C3%A9tico%20(Variante)/README.md) | Coloración de grafos 4×4 | AG con matriz hardcoded, criterio de parada óptimo |

## Compilación general

Todos los programas se compilan con:
```bash
gcc -o <ejecutable> <archivo>.c
```

Para programas que usan MPI:
```bash
mpicc -o <ejecutable> <archivo>.c
mpirun -np <num_procesos> ./<ejecutable> <args>
```

## Dependencias

- `gcc` — compilador C
- `make` (opcional)
- `openmpi-bin` / `libopenmpi-dev` — solo para la versión MPI de Coloración de Grafos

```bash
# Instalar dependencias en Debian/Ubuntu/Kali
sudo apt install gcc openmpi-bin libopenmpi-dev
```
