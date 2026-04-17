#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numOperands;       // Número de operandos
    int length;            // Longitud de cada operando
    char **operands;       // Matriz para almacenar los operandos
    char *result;          // Arreglo para almacenar el resultado
    int carry = 0;         // Variable para almacenar el acarreo
    int i, j;              // Variables de iteración

    // Solicitar la longitud de los operandos
    printf("Ingrese la longitud del operando (maximo 30):\n");
    scanf("%d", &length);

    // Solicitar el número de operandos
    printf("Ingrese el número de operandos:\n");
    scanf("%d", &numOperands);

    // Asignación dinámica de memoria para los operandos y el resultado
    operands = (char **)malloc(numOperands * sizeof(char *));
    for (i = 0; i < numOperands; i++) {
        operands[i] = (char *)malloc((length + 1) * sizeof(char)); // +1 para el carácter nulo
    }
    result = (char *)malloc((length + 2) * sizeof(char)); // +2 para acarreo final y el carácter nulo

    // Solicitar cada operando en formato hexadecimal
    for (i = 0; i < numOperands; i++) {
        printf("Ingrese el valor %d del operando (en formato hexadecimal):\n", i + 1);
        scanf("%s", operands[i]);
    }

    // Inicializar el resultado a 0
    memset(result, '0', length + 1);
    result[length + 1] = '\0';

    // Sumar columna por columna desde la derecha
    for (j = length - 1; j >= 0; j--) {
        int columnSum = carry; // Iniciar la suma de la columna con el acarreo

        // Sumar todos los operandos en la columna j
        for (i = 0; i < numOperands; i++) {
            int hexValue = (operands[i][j] >= '0' && operands[i][j] <= '9') 
                            ? operands[i][j] - '0' 
                            : operands[i][j] - 'A' + 10;
            columnSum += hexValue;
        }

        // Calcular el acarreo para la próxima columna
        carry = columnSum / 16;
        int digit = columnSum % 16;
        result[j + 1] = (digit < 10) ? digit + '0' : digit - 10 + 'A'; // Guardar el dígito en hexadecimal
    }

    // Si hay un acarreo final
    result[0] = (carry > 0) ? carry + '0' : '0';

    // Mostrar los operandos
    printf("La suma de:\n");
    for (i = 0; i < numOperands; i++) {
        printf("operando %d = [ ", i + 1);
        for (j = 0; j < length; j++) {
            printf("%c ", operands[i][j]);
        }
        printf("]\n");
    }

    // Mostrar el resultado (omitir el primer dígito si es '0')
    printf("\nResultado en hexadecimal = [ ");
    for (j = (result[0] == '0') ? 1 : 0; j <= length; j++) {
        printf("%c ", result[j]);
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

