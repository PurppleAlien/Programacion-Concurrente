// Algoritmo Burbuja
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *A; // Apuntador a un arreglo de enteros

// Prototipos de funciones
void burbuja(int n);
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
    burbuja(n);

    printf("Arreglo ordenado:\n");
    imprimeArreglo(n);

    // Liberar memoria
    free(A);

    return 0;
}

// Algoritmo de Burbuja
void burbuja(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j - 1] > A[j]) {
                int temp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = temp;
            }
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

