#include <stdio.h>
#include <stdlib.h>

int main() {
    int numOperands;  // Número de operandos
    int length;       // Longitud de cada operando
    int **operands;   // Matriz para almacenar los operandos en octal
    int *result;      // Arreglo para almacenar el resultado en octal
    int borrow = 0;   // Variable para almacenar el acarreo de resta
    int i, j;         // Variables de iteración

    // Solicitar la longitud de los operandos
    printf("Ingrese la longitud del operando (máximo 30):\n");
    scanf("%d", &length);

    // Solicitar el número de operandos (solo 2 para resta)
    printf("Ingrese el número de operandos (solo 2 para resta):\n");
    scanf("%d", &numOperands);
    if (numOperands != 2) {
        printf("Este programa solo soporta resta entre dos operandos.\n");
        return 1;
    }

    // Asignación dinámica de memoria para los operandos y el resultado
    operands = (int **)malloc(numOperands * sizeof(int *));
    for (i = 0; i < numOperands; i++) {
        operands[i] = (int *)malloc(length * sizeof(int));
    }
    result = (int *)malloc((length + 1) * sizeof(int)); // +1 para el bit de signo

    // Solicitar cada operando
    for (i = 0; i < numOperands; i++) {
        printf("Ingrese el valor %d del operando (en formato octal):\n", i + 1);
        for (j = 0; j < length; j++) {
            scanf("%1d", &operands[i][j]);  // Leer cada dígito octal
        }
    }

    // Realizar la resta columna por columna
    for (j = length - 1; j >= 0; j--) {
        int sub = operands[0][j] - operands[1][j] - borrow;
        if (sub < 0) {
            sub += 8;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[j] = sub;
    }

    // Determinar si el resultado es negativo
    if (borrow) {
        printf("Resultado negativo (subtracción inválida en octal con los operandos dados).\n");
    } else {
        // Mostrar los operandos
        printf("La resta de:\n");
        for (i = 0; i < numOperands; i++) {
            printf("operando %d = [ ", i + 1);
            for (j = 0; j < length; j++) {
                printf("%d ", operands[i][j]);
            }
            printf("]\n");
        }

        // Mostrar el resultado
        printf("\nResultado = [ ");
        for (j = 0; j < length; j++) {
            printf("%d ", result[j]);
        }
        printf("]\n");
    }

    // Liberar memoria
    for (i = 0; i < numOperands; i++) {
        free(operands[i]);
    }
    free(operands);
    free(result);

    return 0;
}

