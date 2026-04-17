// algoritmo Merge Sort 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *A; // Apuntador a un arreglo de enteros
int *B; // Arreglo auxiliar para la fusión

// Prototipos de funciones
void mergeSort(int ini, int fin);
void merge(int ini, int mitad, int fin);
void imprimeArreglo(int n);
void llenarArreglo(int n);

int main() {
    int n;
    
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);

    // Asignar memoria para los arreglos
    A = (int *)malloc(n * sizeof(int));
    B = (int *)malloc(n * sizeof(int));
    if (A == NULL || B == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Llenar el arreglo con valores aleatorios
    llenarArreglo(n);

    printf("Arreglo original:\n");
    imprimeArreglo(n);

    // Ordenar el arreglo usando Merge Sort
    mergeSort(0, n - 1);

    printf("Arreglo ordenado:\n");
    imprimeArreglo(n);

    // Liberar memoria
    free(A);
    free(B);

    return 0;
}

// Función Merge Sort (Ordenamiento por Mezcla)
void mergeSort(int ini, int fin) {
    if (ini < fin) {
        int mitad = (ini + fin) / 2;
        mergeSort(ini, mitad);
        mergeSort(mitad + 1, fin);
        merge(ini, mitad, fin);
    }
}

// Función para mezclar dos subarreglos de A[]
void merge(int ini, int mitad, int fin) {
    int i = ini, j = mitad + 1, k = ini;
    while (i <= mitad && j <= fin) {
        if (A[i] < A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    while (i <= mitad) {
        B[k++] = A[i++];
    }
    while (j <= fin) {
        B[k++] = A[j++];
    }
    for (i = ini; i <= fin; i++) {
        A[i] = B[i];
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

