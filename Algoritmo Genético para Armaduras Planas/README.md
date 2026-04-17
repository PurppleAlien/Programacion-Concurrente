# Algoritmo Genético para Armaduras Planas

**Autores:** Erick Ricardo Martínez Martínez & Juan Antonio Soria Rodriguez  
**Fecha:** 15/11/2024  
**Materia:** Programación Concurrente

## Descripción

Implementación de un algoritmo genético para resolver el problema de optimización de armaduras planas. Lee los parámetros desde un archivo `.dat` y ejecuta las operaciones de evaluación, cruce y mutación sobre una población de cromosomas binarios.

### Operaciones del algoritmo genético
1. **Inicialización** — población aleatoria de cromosomas binarios (0/1).
2. **Evaluación** — calcula peso y función de aptitud (1 / peso+1) para cada cromosoma.
3. **Selección** — función disponible para implementar.
4. **Cruce** — cruce de un punto con probabilidad configurable.
5. **Mutación** — inversión de bits con probabilidad configurable.

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `practica3.c` | Programa principal del algoritmo genético |
| `p3.c` / `p3v2.c` | Versiones intermedias de desarrollo |
| `fork/fork.c` | Ejemplo base de uso de fork() |
| `va/practica3.c` | Variante del programa principal |
| `Practica3_/p2v3.c` | Otra versión de desarrollo |
| `Practica3_/prueba1.dat` | Archivo de datos de prueba |
| `Practica3_/Practica 6/` | Material adicional: grafos y variantes genéticas (carpeta de referencia) |

## Compilación y ejecución

```bash
gcc -o practica3 practica3.c
./practica3
```

## Uso

```
1. Abrir archivo existente e inicializar el Algoritmo Genetico
   → Nombre del archivo (ej: prueba1.dat)
   → Número de cromosomas
   → Número de iteraciones (generaciones)
2. Salir
```

### Formato del archivo `.dat`
```
<prob_cruza_%>
<prob_mutacion_%>
<num_objetos>
<capacidad_maxima>
<peso_1> <longitud_1>
<peso_2> <longitud_2>
...
```

Ejemplo con `prueba1.dat`:
```bash
./practica3
# Opción 1 → archivo: Practica3_/prueba1.dat → cromosomas: 10 → iteraciones: 100
```

## Notas
- `MAX_OBJETOS` y `LONGITUD_CROMOSOMA` están definidos en 60 (modificable).
- La función de selección está declarada pero **pendiente de implementar**.
