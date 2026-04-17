#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipos de funciones
void initializeMatrix(int **matrix, int rows, int cols);
void displayMatrix(int **matrix, int rows, int cols);
void flattenMatrix(int **matrix, int *array, int rows, int cols);
void unflattenMatrix(int *array, int **matrix, int rows, int cols);
void mergeSort(int *arr, int low, int high);
void merge(int *arr, int low, int mid, int high);

// Función principal
int main() {
    int rows, cols, display;

    printf("Dame el numero de filas de tu matriz: ");
    scanf("%d", &rows);
    printf("Dame el numero de columnas de tu matriz: ");
    scanf("%d", &cols);
    printf("Quieres desplegar los elementos del arreglo? 1-> si, 0-> no: ");
    scanf("%d", &display);

    // Reserva de memoria para la matriz
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Inicializar y mostrar la matriz
    initializeMatrix(matrix, rows, cols);
    if (display) {
        printf("\nLos elementos de la matriz desordenada son:\n");
        displayMatrix(matrix, rows, cols);
    }

    // Convertir la matriz en un arreglo plano
    int size = rows * cols;
    int *array = (int *)malloc(size * sizeof(int));
    flattenMatrix(matrix, array, rows, cols);

    // Ordenar usando MergeSort
    clock_t start = clock();
    mergeSort(array, 0, size - 1);
    clock_t end = clock();

    // Reconstruir la matriz ordenada
    unflattenMatrix(array, matrix, rows, cols);


    printf("ORDENAMIENTO POR METODO MERGESORT RECURSIVO\n");
    // Mostrar matriz ordenada
    if (display) {
        printf("Los elementos de la matriz ordenada son:\n");
        displayMatrix(matrix, rows, cols);
    }

    // Mostrar tiempo de ejecución
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo total del metodo MergeSort = %.2f segundos\n", timeTaken);

    // Liberar memoria
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(array);

    return 0;
}

// Funciones auxiliares
void initializeMatrix(int **matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 1000;
        }
    }
}

void displayMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void flattenMatrix(int **matrix, int *array, int rows, int cols) {
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[index++] = matrix[i][j];
        }
    }
}

void unflattenMatrix(int *array, int **matrix, int rows, int cols) {
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = array[index++];
        }
    }
}

void mergeSort(int *arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void merge(int *arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = (int *)malloc(n1 * sizeof(int));
    int *right = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];

    free(left);
    free(right);
}

