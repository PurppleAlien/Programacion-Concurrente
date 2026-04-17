#include <stdio.h>
#include <stdlib.h>

int main() {
    int numOperands; // Número de operandos
    int length; // Longitud de cada operando
    int **operands; // Matriz para almacenar los operandos en binario
    int *result; // Arreglo para almacenar el resultado en binario
    int decimalResult = 0; // Resultado en decimal
    int i, j; // Variables de iteración

    // Solicitar la longitud de los operandos
    printf("Ingrese la longitud del operando (maximo 30):\n");
    scanf("%d", &length);

    // Solicitar el número de operandos (solo 2 para resta)
    printf("Ingrese el numero de operandos (solo 2 para resta):\n");
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
        printf("Ingrese el valor %d del operando (en formato binario):\n", i + 1);
        for (j = 0; j < length; j++) {
            scanf("%1d", &operands[i][j]); // Leer cada dígito binario
        }
    }

    // Convertir los operandos a decimal
    int decimalOperands[2] = {0, 0}; // Arreglos para almacenar los operandos en decimal
    for (i = 0; i < numOperands; i++) {
        int power = 1;
        for (j = length - 1; j >= 0; j--) {
            decimalOperands[i] += operands[i][j] * power;
            power *= 2;
        }
    }

    // Realizar la resta en decimal
    decimalResult = decimalOperands[0] - decimalOperands[1];

    // Verificar si el resultado es negativo
    if (decimalResult < 0) {
        // Convertir el resultado al complemento a 2
        int absResult = -decimalResult;
        for (j = length; j >= 1; j--) {
            result[j] = absResult % 2;
            absResult /= 2;
        }

        // Aplicar complemento a 1 (invertir bits)
        for (j = 1; j <= length; j++) {
            result[j] = result[j] == 0 ? 1 : 0;
        }

        // Sumar 1 para obtener complemento a 2
        int carry = 1;
        for (j = length; j >= 1; j--) {
            int sum = result[j] + carry;
            result[j] = sum % 2;
            carry = sum / 2;
        }

        // Colocar el bit de signo (1 para negativo)
        result[0] = 1;
    } else {
        // Representar el resultado en formato signo y magnitud
        for (j = length; j >= 1; j--) {
            result[j] = decimalResult % 2;
            decimalResult /= 2;
        }

        // Colocar el bit de signo (0 para positivo)
        result[0] = 0;
    }

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
    printf("\nResultado en binario (con bit de signo) = [ ");
    for (j = 0; j <= length; j++) {
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

