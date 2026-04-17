#include <stdio.h>
#include <stdlib.h>

int main() {
    int numOperands; // Número de operandos
    int length; // Longitud de cada operando
    int **operands; // Matriz para almacenar los operandos
    int *result; // Arreglo para almacenar el resultado
    int carry = 0; // Variable para almacenar el acarreo
    int i, j; // Variables de iteración

    // Solicitar la longitud de los operandos
    printf("Ingrese la longitud del operando (maximo 30):\n");
    scanf("%d", &length);

    // Solicitar el número de operandos
    printf("Ingrese el numero de operandos:\n");
    scanf("%d", &numOperands);

    // Asignación dinámica de memoria para los operandos y el resultado
    operands = (int **)malloc(numOperands * sizeof(int *));
    for (i = 0; i < numOperands; i++) {
        operands[i] = (int *)malloc(length * sizeof(int));
    }
    result = (int *)malloc(length * sizeof(int));

    // Solicitar cada operando
    for (i = 0; i < numOperands; i++) {
        printf("Ingrese el valor %d del operando (en formato binario):\n", i + 1);
        for (j = 0; j < length; j++) {
            scanf("%1d", &operands[i][j]); // Leer cada dígito binario
        }
    }

    // Inicializar el resultado a 0
    for (j = 0; j < length; j++) {
        result[j] = 0;
    }

    // Sumar columna por columna
    for (j = length - 1; j >= 0; j--) {
        int columnSum = carry; // Iniciar la suma de la columna con el acarreo

        // Sumar todos los operandos en la columna j
        for (i = 0; i < numOperands; i++) {
            columnSum += operands[i][j];
        }

        // Calcular el acarreo para la próxima columna
        carry = columnSum / 2;
        result[j] = columnSum % 2; // Guardar el resultado en la posición correspondiente
    }

    // Mostrar los operandos
    printf("La suma de:\n");
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

    // Liberar memoria
    for (i = 0; i < numOperands; i++) {
        free(operands[i]);
    }
    free(operands);
    free(result);

    return 0;
}

