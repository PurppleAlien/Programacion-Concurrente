#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Funciones de ordenamiento
void mergeSort(int *arr, int low, int high);
void merge(int *arr, int low, int mid, int high);

// Función para inicializar la matriz con valores aleatorios
void initializeMatrix(int **matrix, int rows, int cols);

// Función para imprimir la matriz
void printMatrix(int **matrix, int rows, int cols);

// Función para convertir la matriz a un arreglo unidimensional
void matrixToArray(int **matrix, int *arr, int rows, int cols);

// Función para convertir el arreglo unidimensional a una matriz
void arrayToMatrix(int *arr, int **matrix, int rows, int cols);

// Función principal
int main() {
    int rows, cols, display;

    printf("Dame el numero de filas de tu matriz: ");
    scanf("%d", &rows);
    printf("Dame el numero de columnas de tu matriz: ");
    scanf("%d", &cols);

    printf("Quieres desplegar los elementos del arreglo? 1-> si, 0-> no: ");
    scanf("%d", &display);

    // Crear matriz dinámica
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    if (!matrix) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    initializeMatrix(matrix, rows, cols);

    // Mostrar la matriz original si el usuario lo desea
    if (display) {
        printf("\nLos elementos de la matriz desordenada son:\n");
        printMatrix(matrix, rows, cols);
    }

    // Convertir la matriz a un arreglo unidimensional
    int size = rows * cols;
    int *arr = malloc(size * sizeof(int));
    if (!arr) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    matrixToArray(matrix, arr, rows, cols);

    // Medir el tiempo de ejecución
    clock_t start = clock();

    pid_t pid = fork();
    if (pid == 0) {  // Proceso cliente
        mergeSort(arr, 0, size / 2 - 1);  // Ordenar la primera mitad
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {  // Proceso servidor
        mergeSort(arr, size / 2, size - 1);  // Ordenar la segunda mitad
        wait(NULL);  // Esperar al cliente
        merge(arr, 0, size / 2 - 1, size - 1);  // Combinar las dos mitades
    } else {
        perror("Error al crear el proceso");
        exit(EXIT_FAILURE);
    }

    clock_t end = clock();
    double totalTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Convertir el arreglo unidimensional a una matriz
    arrayToMatrix(arr, matrix, rows, cols);

    // Mostrar la matriz ordenada si el usuario lo desea
    printf("\nORDENAMIENTO POR EL METODO MERGESORT RECURSIVO PARALELO\n");
    if (display) {
        printf("Los elementos de la matriz ordenada son:\n");
        printMatrix(matrix, rows, cols);
    }

    printf("\nTiempo total del metodo mergesort = %.2f segundos\n", totalTime);

    // Liberar memoria
    free(arr);
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

// Implementaciones de funciones
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

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

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

void initializeMatrix(int **matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 1000;
        }
    }
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixToArray(int **matrix, int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i * cols + j] = matrix[i][j];
        }
    }
}

void arrayToMatrix(int *arr, int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = arr[i * cols + j];
        }
    }
}

