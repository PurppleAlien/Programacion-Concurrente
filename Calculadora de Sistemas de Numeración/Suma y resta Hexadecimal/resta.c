#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numOperands;       // Número de operandos (debería ser 2 para resta)
    int length;            // Longitud de cada operando
    char **operands;       // Matriz para almacenar los operandos
    char *result;          // Arreglo para almacenar el resultado
    int borrow = 0;        // Variable para almacenar el préstamo
    int i, j;              // Variables de iteración

    // Solicitar la longitud de los operandos
    printf("Ingrese la longitud del operando (maximo 30):\n");
    scanf("%d", &length);

    // Solicitar el número de operandos (solo 2 para resta)
    numOperands = 2;

    // Asignación dinámica de memoria para los operandos y el resultado
    operands = (char **)malloc(numOperands * sizeof(char *));
    for (i = 0; i < numOperands; i++) {
        operands[i] = (char *)malloc((length + 1) * sizeof(char)); // +1 para el carácter nulo
    }
    result = (char *)malloc((length + 1) * sizeof(char)); // +1 para el carácter nulo

    // Solicitar cada operando en formato hexadecimal
    for (i = 0; i < numOperands; i++) {
        printf("Ingrese el valor %d del operando (en formato hexadecimal):\n", i + 1);
        scanf("%s", operands[i]);
    }

    // Inicializar el resultado a 0
    memset(result, '0', length);
    result[length] = '\0'; // Asegurar que sea un string válido

    // Restar columna por columna desde la derecha
    for (j = length - 1; j >= 0; j--) {
        int digit1 = (operands[0][j] >= '0' && operands[0][j] <= '9') 
                     ? operands[0][j] - '0' 
                     : operands[0][j] - 'A' + 10;
        int digit2 = (operands[1][j] >= '0' && operands[1][j] <= '9') 
                     ? operands[1][j] - '0' 
                     : operands[1][j] - 'A' + 10;

        // Restar los dígitos y el préstamo actual
        int diff = digit1 - digit2 - borrow;

        // Si el resultado es negativo, ajustar con el préstamo
        if (diff < 0) {
            diff += 16;
            borrow = 1; // Se necesita un préstamo
        } else {
            borrow = 0; // No hay préstamo
        }

        // Almacenar el dígito en el resultado en formato hexadecimal
        result[j] = (diff < 10) ? diff + '0' : diff - 10 + 'A';
    }

    // Mostrar los operandos
    printf("La resta de:\n");
    for (i = 0; i < numOperands; i++) {
        printf("operando %d = [ ", i + 1);
        for (j = 0; j < length; j++) {
            printf("%c ", operands[i][j]);
        }
        printf("]\n");
    }

    // Mostrar el resultado (omitir ceros iniciales)
    printf("\nResultado en hexadecimal = [ ");
    int leadingZeros = 1; // Para omitir ceros iniciales
    for (j = 0; j < length; j++) {
        if (result[j] != '0') leadingZeros = 0; // Encontrar el primer dígito no cero
        if (!leadingZeros) {
            printf("%c ", result[j]);
        }
    }
    if (leadingZeros) {
        printf("0 "); // Si el resultado es cero
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

