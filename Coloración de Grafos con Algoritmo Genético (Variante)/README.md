# Coloración de Grafos con Algoritmo Genético (Variante)

**Autor:** Soria Rodriguez Juan Antonio G.  
**Materia:** Programación Concurrente

## Descripción

Resuelve el problema de **coloración de grafos** (problema de 4 colores en mapas) mediante un algoritmo genético. A diferencia de la Práctica 6, trabaja con una **matriz de adyacencia fija 4×4** (16 regiones) definida en el código, con población de tamaño 8 y criterio de parada cuando el fitness es 0.

### Diferencias respecto a Coloración de Grafos (versión completa)

| Característica | Versión completa | Esta variante |
|---|---|---|
| Grafo | Desde archivo `.txt` | Hardcoded en el código |
| Tamaño | Hasta 1000 regiones | 16 regiones (4×4) |
| Población | Configurable | Fija (8 cromosomas) |
| Parada | 500 iteraciones | Fitness=0 o 1000 iteraciones |

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `Genetico.c` | Programa principal del algoritmo genético 4×4 |
| `VisualizacionGrafos.c` | Herramienta de visualización de grafos |
| `graf*.txt` | Archivos de grafos de distintos tamaños (para uso con VisualizacionGrafos) |

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
cd Practica7

# Algoritmo genético
gcc -o Genetico Genetico.c
./Genetico

# Visualizador de grafos
gcc -o VisualizacionGrafos VisualizacionGrafos.c
./VisualizacionGrafos graf10x10.txt
```

## Uso — Genetico

El programa **no pide argumentos**. Corre directamente:

```
Iteración 0: Mejor fitness = 8
Iteración 1: Mejor fitness = 6
...
¡Óptimo encontrado!
Cromosoma: [0, 1, 2, 3, 1, 0, 2, 1, ...]
```

- **Fitness = 0** → coloración válida encontrada (ningún par de regiones adyacentes comparte color).
- Si no converge en 1000 iteraciones, muestra el mensaje `No se alcanzó el óptimo...`.

## Parámetros configurables (en el código)

| Constante | Valor | Descripción |
|---|---|---|
| `NUM_REGIONES` | 16 | Número de nodos del grafo |
| `TAMANO_POBLACION` | 8 | Cromosomas por generación |
| `NUM_COLORES` | 4 | Colores disponibles |
| `MAX_ITERACIONES` | 1000 | Límite de generaciones |

## Notas
- La matriz de adyacencia está **parcialmente definida** en el código (solo 5 de 16 filas tienen valores completos). Las filas restantes están inicializadas en 0.
- Para usar grafos más complejos, se recomienda usar la versión completa con archivos `.txt`.
