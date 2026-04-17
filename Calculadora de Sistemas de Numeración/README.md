# Práctica 1 — Calculadora de Sistemas de Numeración

**Alumno:** Soria Rodriguez Juan Antonio G.  
**Matrícula:** 2203041232  
**Materia:** Programación Concurrente

## Descripción

Calculadora interactiva que realiza sumas y restas en sistemas de numeración binario, octal y hexadecimal. Incluye versiones modulares (un archivo por operación) y una versión final integrada con menú completo.

## Estructura de archivos

| Archivo | Descripción |
|---|---|
| `Practia 1 final/Practica1.c` | Versión final: menú completo con sumas y restas en los tres sistemas |
| `Practica 1/Practica1_A.c` | Lista simple ligada con operaciones: insertar, buscar, eliminar, vaciar |
| `Suma y resta Hexadecimal/suma.c` | Suma hexadecimal de N operandos |
| `Suma y resta Hexadecimal/resta.c` | Resta hexadecimal entre dos operandos |
| `suma y resta binaria/suma.c` | Suma binaria de N operandos con acarreo |
| `suma y resta octal/suma.c` | Suma octal de N operandos con acarreo |

## Compilación y ejecución

### Versión final (recomendada)
```bash
cd "Practia 1 final"
gcc -o Practica1 Practica1.c
./Practica1
```

### Versiones individuales
```bash
# Suma hexadecimal
cd "Suma y resta Hexadecimal"
gcc -o suma suma.c && ./suma

# Resta hexadecimal
gcc -o resta resta.c && ./resta

# Suma binaria
cd "../suma y resta binaria"
gcc -o suma suma.c && ./suma

# Suma octal
cd "../suma y resta octal"
gcc -o suma suma.c && ./suma
```

### Lista ligada
```bash
cd "Practica 1"
gcc -o Practica1_A Practica1_A.c
./Practica1_A
```

## Uso — Versión final

```
1. Sumas
   1. Sistema Binario  → ingresa longitud y número de operandos en bits
   2. Sistema Octal    → ingresa longitud y número de operandos en dígitos octales
   3. Sistema Hexadecimal → ingresa longitud y operandos en mayúsculas (ej: A3F)
2. Restas             → solo acepta 2 operandos
3. Salir
```

## Notas
- Los operandos hexadecimales deben ingresarse en **mayúsculas**.
- La longitud máxima soportada es **30 dígitos**.
- La resta binaria devuelve el resultado con **bit de signo** (complemento a 2 si es negativo).
