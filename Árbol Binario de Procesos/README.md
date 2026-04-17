# Árbol Binario de Procesos

**Autor:** Soria Rodriguez Juan Antonio G.  
**Materia:** Programación Concurrente

## Descripción

Genera un árbol binario de procesos con la profundidad indicada por el usuario. Cada nodo del árbol es un proceso del sistema operativo creado con `fork()`. Se implementan dos estrategias:

| Programa | Estrategia |
|---|---|
| `Practica4_A.c` | **Iterativa** — usa una cola (BFS) para crear los procesos nivel por nivel |
| `Practica4_B.c` | **Recursiva** — crea los hijos de forma recursiva en profundidad (DFS) |

## Compilación y ejecución

```bash
# Programa A — iterativo
gcc -o Practica4_A Practica4_A.c
./Practica4_A

# Programa B — recursivo
gcc -o Practica4_B Practica4_B.c
./Practica4_B
```

Ambos piden la **profundidad del árbol** al iniciar:
```
Proporciona el nivel de profundidad de tu Arbol de procesos: 3
```

## Salida esperada

```
UID       PID     PPID    TTY       COMMAND
usuario   12345   12344   /dev/pts/0  ./Primera_Parte_L
usuario   12346   12344   /dev/pts/0  ./Primera_Parte_R
...
```

Para observar el árbol de procesos mientras el programa corre (tiene un `sleep(10)`):
```bash
# En otra terminal
pstree -p <PID_del_proceso_raiz>
# o bien
ps -ef | grep Practica4
```

## Advertencia

`Practica4_A.c` tiene un **warning de posible buffer overflow** al concatenar `_L`/`_R` al nombre del proceso. El buffer `new_name` es de 50 bytes pero el nombre base puede llegar a los mismos 50, causando desbordamiento en árboles muy profundos. Se recomienda aumentar `new_name` a `char new_name[100]` en las líneas 100 y 107.

## Notas
- Cada proceso hijo duerme **10 segundos** antes de terminar, lo que permite observar el árbol con `pstree`.
- El proceso padre espera a sus hijos con `wait(NULL)`.
- Se recomienda usar una **profundidad máxima de 4** para evitar crear demasiados procesos (2^n hijos).
