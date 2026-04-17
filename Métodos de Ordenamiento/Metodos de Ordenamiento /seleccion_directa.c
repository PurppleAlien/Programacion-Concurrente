// Algoritmo de seleccion directa

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *A; // Apuntador a un arreglo de enteros

// Prototipos de funciones
int BuscaMin(int ini, int fin);
void seleccionDirecta(int n);
void imprimeArreglo(int n);
void llenarArreglo(int n);

int main() {
    int n;
    
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);

    // Asignar memoria para el arreglo
    A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Llenar el arreglo con valores aleatorios
    llenarArreglo(n);

    printf("Arreglo original:\n");
    imprimeArreglo(n);

    // Ordenar el arreglo
    seleccionDirecta(n);

    printf("Arreglo ordenado:\n");
    imprimeArreglo(n);

    // Liberar memoria
    free(A);

    return 0;
}

// Función que busca el índice del valor mínimo en el rango [ini, fin]
int BuscaMin(int ini, int fin) {
    if (ini < fin) {
        int min = A[ini];
        int pos_min = ini;
        for (int i = ini + 1; i <= fin; i++) {
            if (A[i] < min) {
                min = A[i];
                pos_min = i;
            }
        }
        return pos_min;
    } else {
        return -1; // valor_erroneo
    }
}

// Algoritmo de Selección Directa utilizando la función BuscaMin
void seleccionDirecta(int n) {
    int temp, pos_min;
    for (int i = 0; i < n - 1; i++) {
        pos_min = BuscaMin(i, n - 1);
        if (pos_min != -1) {
            temp = A[i];
            A[i] = A[pos_min];
            A[pos_min] = temp;
        }
    }
}

// Función para imprimir el arreglo
void imprimeArreglo(int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Función para llenar el arreglo con valores aleatorios
void llenarArreglo(int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // Generar números aleatorios entre 0 y 99
    }
}

