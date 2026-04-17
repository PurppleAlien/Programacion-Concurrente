#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int opcion, subopcion, numOperands, length, carry = 0,borrow = 0;
    int **operands, *result;
    char **hexOperands, *hexResult;
    int i, j, decimalResult = 0;
    int decimalOperands[2];

    do {
        printf("Bienvenido a la calculadora de sistemas de numeracion (2,8,16)\n");
        printf("1. Sumas\n");
        printf("2. Restas\n");
        printf("3. Salir del programa\n");
        printf("Elije una de las opciones anteriores porfavor : ");
        scanf("%d", &opcion);

        switch (opcion) {
            ////sumas////
            case 1:
                do {
                    printf("Menu para realizar Sumas\n");
                    printf("1. Sumas en Sistema de Numeracion Binario\n");
                    printf("2. Sumas en Sistema de Numeracion Octal\n");
                    printf("3. Sumas en Sistema de Numeracion Hexadecimal\n");
                    printf("4. Salir del Programa\n");
                    printf("Elije una de las opciones anteriores porfavor : ");
                    scanf("%d", &subopcion);

                    if (subopcion == 1) {
                        // Suma en sistema binario
                        printf("Ingrese la longitud del operando (maximo 30):\n");
                        scanf("%d", &length);
                        printf("Ingrese el numero de operandos:\n");
                        scanf("%d", &numOperands);

                        operands = (int **)malloc(numOperands * sizeof(int *));
                        for (i = 0; i < numOperands; i++) {
                            operands[i] = (int *)malloc(length * sizeof(int));
                        }
                        result = (int *)malloc(length * sizeof(int));

                        for (i = 0; i < numOperands; i++) {
                            printf("Ingrese el valor %d del operando (en formato binario):\n", i + 1);
                            for (j = 0; j < length; j++) {
                                scanf("%1d", &operands[i][j]);
                            }
                        }

                        for (j = 0; j < length; j++) {
                            result[j] = 0;
                        }

                        for (j = length - 1; j >= 0; j--) {
                            int columnSum = carry;
                            for (i = 0; i < numOperands; i++) {
                                columnSum += operands[i][j];
                            }
                            carry = columnSum / 2;
                            result[j] = columnSum % 2;
                        }

                        printf("La suma de:\n");
                        for (i = 0; i < numOperands; i++) {
                            printf("operando %d = [ ", i + 1);
                            for (j = 0; j < length; j++) {
                                printf("%d ", operands[i][j]);
                            }
                            printf("]\n");
                        }
                        printf("\nResultado = [ ");
                        for (j = 0; j < length; j++) {
                            printf("%d ", result[j]);
                        }
                        printf("]\n");

                        for (i = 0; i < numOperands; i++) {
                            free(operands[i]);
                        }
                        free(operands);
                        free(result);

                        printf("<<< Regresando al menu Principal >>>\n");
                        printf("Presione una tecla para continuar ...\n");
                        getchar();
                        getchar();
                    } else if (subopcion == 2) {
                        // Suma en sistema octal
                        printf("Ingrese la longitud del operando (maximo 30):\n");
                        scanf("%d", &length);
                        printf("Ingrese el numero de operandos:\n");
                        scanf("%d", &numOperands);

                        operands = (int **)malloc(numOperands * sizeof(int *));
                        for (i = 0; i < numOperands; i++) {
                            operands[i] = (int *)malloc(length * sizeof(int));
                        }
                        result = (int *)malloc(length * sizeof(int));

                        for (i = 0; i < numOperands; i++) {
                            printf("Ingrese el valor %d del operando (en formato octal):\n", i + 1);
                            for (j = 0; j < length; j++) {
                                scanf("%1d", &operands[i][j]);
                            }
                        }

                        for (j = 0; j < length; j++) {
                            result[j] = 0;
                        }

                        for (j = length - 1; j >= 0; j--) {
                            int columnSum = carry;
                            for (i = 0; i < numOperands; i++) {
                                columnSum += operands[i][j];
                            }
                            carry = columnSum / 8;
                            result[j] = columnSum % 8;
                        }

                        printf("La suma de:\n");
                        for (i = 0; i < numOperands; i++) {
                            printf("operando %d = [ ", i + 1);
                            for (j = 0; j < length; j++) {
                                printf("%d ", operands[i][j]);
                            }
                            printf("]\n");
                        }
                        printf("\nResultado = [ ");
                        for (j = 0; j < length; j++) {
                            printf("%d ", result[j]);
                        }
                        printf("]\n");

                        for (i = 0; i < numOperands; i++) {
                            free(operands[i]);
                        }
                        free(operands);
                        free(result);

                        printf("<<< Regresando al menu Principal >>>\n");
                        printf("Presione una tecla para continuar ...\n");
                        getchar();
                        getchar();
                    } else if (subopcion == 3) {
                        // Suma en sistema hexadecimal
                        printf("Ingrese la longitud del operando (maximo 30):\n");
                        scanf("%d", &length);
                        printf("Ingrese el numero de operandos:\n");
                        scanf("%d", &numOperands);

                        hexOperands = (char **)malloc(numOperands * sizeof(char *));
                        for (i = 0; i < numOperands; i++) {
                            hexOperands[i] = (char *)malloc((length + 1) * sizeof(char));
                        }
                        hexResult = (char *)malloc((length + 2) * sizeof(char));

                        for (i = 0; i < numOperands; i++) {
                            printf("Ingrese el valor %d del operando (en formato hexadecimal):\n", i + 1);
                            scanf("%s", hexOperands[i]);
                        }

                        memset(hexResult, '0', length + 1);
                        hexResult[length + 1] = '\0';

                        for (j = length - 1; j >= 0; j--) {
                            int columnSum = carry;
                            for (i = 0; i < numOperands; i++) {
                                int hexValue = (hexOperands[i][j] >= '0' && hexOperands[i][j] <= '9')
                                               ? hexOperands[i][j] - '0'
                                               : hexOperands[i][j] - 'A' + 10;
                                columnSum += hexValue;
                            }
                            carry = columnSum / 16;
                            int digit = columnSum % 16;
                            hexResult[j + 1] = (digit < 10) ? digit + '0' : digit - 10 + 'A';
                        }

                        hexResult[0] = (carry > 0) ? carry + '0' : '0';

                        printf("La suma de:\n");
                        for (i = 0; i < numOperands; i++) {
                            printf("operando %d = [ ", i + 1);
                            for (j = 0; j < length; j++) {
                                printf("%c ", hexOperands[i][j]);
                            }
                            printf("]\n");
                        }
                        printf("\nResultado en hexadecimal = [ ");
                        for (j = (hexResult[0] == '0') ? 1 : 0; j <= length; j++) {
                            printf("%c ", hexResult[j]);
                        }
                        printf("]\n");

                        for (i = 0; i < numOperands; i++) {
                            free(hexOperands[i]);
                        }
                        free(hexOperands);
                        free(hexResult);

                        printf("<<< Regresando al menu Principal >>>\n");
                        printf("Presione una tecla para continuar ...\n");
                        getchar();
                        getchar();
                    }
                } while (subopcion != 4);
                break;
                
                /////restas /// 

            case 2: do { 
                printf("Menu para realizar Restas\n"); 
                printf("1. Restas en Sistema de Numeracion Binario\n"); 
                printf("2. Restas en Sistema de Numeracion Octal\n"); 
                printf("3. Restas en Sistema de Numeracion Hexadecimal\n"); 
                printf("4. Salir del Programa\n"); 
                printf("Elije una de las opciones anteriores porfavor : "); 
                scanf("%d", &subopcion); 
                
                if (subopcion == 1) { 
                    printf("Ingrese la longitud del operando (maximo 30):\n"); 
                    scanf("%d", &length); 
                    printf("Ingrese el numero de operandos (solo 2 para resta):\n"); 
                    scanf("%d", &numOperands); 
                    
                    if (numOperands != 2) { 
                        printf("Este programa solo soporta resta entre dos operandos.\n"); 
                        break; 
                    } 
                    
                    operands = (int **)malloc(numOperands * sizeof(int *)); 
                    for (i = 0; i < numOperands; i++) { operands[i] = (int *)malloc(length * sizeof(int)); 
                    } 
                    
                    result = (int *)malloc((length + 1) * sizeof(int)); 
                    for (i = 0; i < numOperands; i++) { 
                        printf("Ingrese el valor %d del operando (en formato binario):\n", i + 1); 
                        for (j = 0; j < length; j++) { 
                            scanf("%1d", &operands[i][j]);    
                        } 
                        
                    } 
                        for (i = 0; i < numOperands; i++) { 
                            int power = 1; 
                        decimalOperands[i] = 0; 
                        for (j = length - 1; j >= 0; j--) { 
                            decimalOperands[i] += operands[i][j] * power; 
                            power *= 2; 
                        } 
                            
                        } decimalResult = decimalOperands[0] - decimalOperands[1]; 
                        
                        if (decimalResult < 0) { 
                            int absResult = -decimalResult; 
                            for (j = length; j >= 1; j--) { 
                                result[j] = absResult % 2; 
                                absResult /= 2;     
                        } 
                        for (j = 1; j <= length; j++) { 
                            result[j] = result[j] == 0 ? 1 : 0;    
                        } 
                        
                        carry = 1; 
                        for (j = length; j >= 1; j--) { int sum = result[j] + carry; 
                        result[j] = sum % 2; 
                        carry = sum / 2; 
                            
                        } 
                        result[0] = 1;    
                        }else{ 
                            for (j = length; j >= 1; j--) 
                            { 
                                result[j] = decimalResult % 2; 
                            decimalResult /= 2; 
                                
                            } 
                            result[0] = 0; 
                            
                        } 
                        printf("La resta de:\n"); 
                        for (i = 0; i < numOperands; i++){ 
                            printf("operando %d = [ ", i + 1); 
                            for (j = 0; j < length; j++) 
                            { 
                                printf("%d ", operands[i][j]); 
                                
                            } 
                            printf("]\n"); 
                            
                        } 
                        printf("\nResultado en binario (con bit de signo) = [ "); 
                        for (j = 0; j <= length; j++) 
                        { 
                            printf("%d ", result[j]); 
                            
                        } 
                        printf("]\n"); 
                        for (i = 0; i < numOperands; i++) { free(operands[i]); 
                            
                        } 
                        free(operands); 
                        free(result); 
                        printf("<<< Regresando al menu Principal >>>\n"); 
                        printf("Presione una tecla para continuar ...\n"); 
                        getchar(); 
                        getchar(); 
                } else if (subopcion == 2) { 
                    printf("Ingrese la longitud del operando (máximo 30):\n"); 
                    scanf("%d", &length); 
                    printf("Ingrese el número de operandos (solo 2 para resta):\n"); 
                    scanf("%d", &numOperands); 
                    
                    if (numOperands != 2) { 
                        printf("Este programa solo soporta resta entre dos operandos.\n"); 
                        break; } operands = (int **)malloc(numOperands * sizeof(int *)); 
                        for (i = 0; i < numOperands; i++) { 
                            operands[i] = (int *)malloc(length * sizeof(int)); 
                            
                        } 
                        result = (int *)malloc((length + 1) * sizeof(int)); 
                        for (i = 0; i < numOperands; i++) 
                        { 
                            printf("Ingrese el valor %d del operando (en formato octal):\n", i + 1); 
                            for (j = 0; j < length; j++) 
                            { 
                                scanf("%1d", &operands[i][j]); 
                                
                            } 
                            
                        } 
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
                        if (borrow) { 
                            printf("Resultado negativo (subtracción inválida en octal con los operandos dados).\n"); 
                            
                        } else { 
                            printf("La resta de:\n"); 
                            for (i = 0; i < numOperands; i++) { 
                                printf("operando %d = [ ", i + 1); 
                                for (j = 0; j < length; j++) { 
                                    printf("%d ", operands[i][j]); 
                                    
                                } 
                                printf("]\n"); 
                                
                            } 
                            printf("\nResultado = [ "); 
                            for (j = 0; j < length; j++) { 
                                printf("%d ", result[j]); 
                                
                            } 
                            printf("]\n"); 
                            
                        } 
                        for (i = 0; i < numOperands; i++) { 
                            free(operands[i]); 
                            
                        } 
                        free(operands); 
                        free(result); 
                        printf("<<< Regresando al menu Principal >>>\n"); 
                        printf("Presione una tecla para continuar ...\n"); 
                        getchar(); 
                        getchar();
                        
                }else if (subopcion == 3) { 
                    printf("Ingrese la longitud del operando (maximo 30):\n"); 
                    scanf("%d", &length); 
                    printf("Ingrese el número de operandos (solo 2 para resta):\n"); 
                    scanf("%d", &numOperands); 
                    
                    if (numOperands != 2) { 
                        printf("Este programa solo soporta resta entre dos operandos.\n"); 
                        break;  
                    } 
                    
                    hexOperands = (char **)malloc(numOperands * sizeof(char *)); 
                    for (i = 0; i < numOperands; i++) { 
                        hexOperands[i] = (char *)malloc((length + 1) * sizeof(char)); // +1 para el carácter nulo 
                        } 
                        hexResult = (char *)malloc((length + 1) * sizeof(char)); // +1 para el carácter nulo 
                       
                        for (i = 0; i < numOperands; i++) { 
                            printf("Ingrese el valor %d del operando (en formato hexadecimal y usando letras Mayusculas):\n", i + 1); 
                            scanf("%s", hexOperands[i]); 
                            
                        } 
                        memset(hexResult, '0', length); 
                        hexResult[length] = '\0'; // Asegurar que sea un string válido 
                        for (j = length - 1; j >= 0; j--) { 
                            int digit1 = (hexOperands[0][j] >= '0' && hexOperands[0][j] <= '9')
                            ? hexOperands[0][j] - '0' 
                            : hexOperands[0][j] - 'A' + 10; 
                            int digit2 = (hexOperands[1][j] >= '0' && hexOperands[1][j] <= '9') 
                            ? hexOperands[1][j] - '0' 
                            : hexOperands[1][j] - 'A' + 10; 
                            int diff = digit1 - digit2 - borrow; 
                            
                            if (diff < 0) { 
                                diff += 16; 
                                borrow = 1; 
                                
                            } else { 
                                borrow = 0; 
                                
                            } 
                            hexResult[j] = (diff < 10) ? diff + '0' : diff - 10 + 'A';
                            } 
                            printf("La resta de:\n"); 
                            for (i = 0; i < numOperands; i++) { 
                                printf("operando %d = [ ", i + 1); 
                                for (j = 0; j < length; j++) { 
                                    printf("%c ", hexOperands[i][j]); 
                                    
                                } 
                                printf("]\n"); 
                                
                            } 
                            printf("\nResultado en hexadecimal = [ "); 
                            int leadingZeros = 1; 
                            for (j = 0; j < length; j++) { 
                                if (hexResult[j] != '0') leadingZeros = 0; 
                                if (!leadingZeros) 
                                { 
                                    printf("%c ", hexResult[j]); 
                                    
                                } 
                                
                            } 
                            if (leadingZeros) { 
                                printf("0 "); 
                                
                            } 
                            printf("]\n"); 
                            for (i = 0; i < numOperands; i++) { 
                                free(hexOperands[i]); 
                                
                            } 
                            free(hexOperands); 
                            free(hexResult); 
                            printf("<<< Regresando al menu Principal >>>\n"); 
                            printf("Presione una tecla para continuar ...\n"); 
                            getchar(); 
                            getchar();     
                }
                
            } while (subopcion != 4); 
            break; 
            
            case 3: 
            printf("Saliendo del programa...\n"); 
            break; 
            default: 
            printf("Opcion no valida. Por favor intente nuevamente.\n"); 
            break; 
            
        } 
        
    } while (opcion != 3); 
    return 0; }
