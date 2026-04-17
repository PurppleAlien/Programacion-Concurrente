#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Función para inicializar un arreglo con valores aleatorios
void initializeArray(int *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Valores aleatorios entre 0 y 999
    }
}

// Función para medir el tiempo de ejecución
double measureTime(void (*sortFunction)(int *, int), int *arr, int size) {
    clock_t start = clock();
    sortFunction(arr, size);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Función especial para medir tiempo de mergeSort
double measureMergeSortTime(void (*sortFunction)(int *, int, int), int *arr, int low, int high) {
    clock_t start = clock();
    sortFunction(arr, low, high);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Algoritmo de ordenamiento Burbuja
void bubbleSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Algoritmo de ordenamiento Selección
void selectionSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

// Algoritmo de ordenamiento Inserción
void insertionSort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Algoritmo de MergeSort
void merge(int *arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int *arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int size, display;

    printf("Dame el tamano de los elementos del arreglo: ");
    scanf("%d", &size);

    printf("Quieres desplegar los elementos del arreglo? 1-> si, 0-> no: ");
    scanf("%d", &display);

    // Crear arreglos dinámicos
    int *arrBubble = malloc(size * sizeof(int));
    int *arrSelection = malloc(size * sizeof(int));
    int *arrInsertion = malloc(size * sizeof(int));
    int *arrMerge = malloc(size * sizeof(int));

    if (!arrBubble || !arrSelection || !arrInsertion || !arrMerge) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    // Inicializar arreglos con valores aleatorios
    initializeArray(arrBubble, size);
    for (int i = 0; i < size; i++) {
        arrSelection[i] = arrBubble[i];
        arrInsertion[i] = arrBubble[i];
        arrMerge[i] = arrBubble[i];
    }

    pid_t pid;
    printf("\nORDENAMIENTO CONCURRENTE\n");
    for (int i = 0; i < 4; i++) {
        pid = fork();
        if (pid == 0) {
            // Proceso esclavo
            double timeTaken = 0.0;
            switch (i) {
                case 0:
                    timeTaken = measureTime(bubbleSort, arrBubble, size);
                    printf("Metodo Burbuja: %.2f segundos\n", timeTaken);
                    if (display) {
                        printf("Arreglo ordenado por Burbuja: ");
                        for (int j = 0; j < size; j++) printf("%d ", arrBubble[j]);
                        printf("\n");
                    }
                    break;
                case 1:
                    timeTaken = measureTime(selectionSort, arrSelection, size);
                    printf("Metodo Seleccion Directa: %.2f segundos\n", timeTaken);
                    if (display) {
                        printf("Arreglo ordenado por Seleccion: ");
                        for (int j = 0; j < size; j++) printf("%d ", arrSelection[j]);
                        printf("\n");
                    }
                    break;
                case 2:
                    timeTaken = measureTime(insertionSort, arrInsertion, size);
                    printf("Metodo Insercion Directa: %.2f segundos\n", timeTaken);
                    if (display) {
                        printf("Arreglo ordenado por Insercion: ");
                        for (int j = 0; j < size; j++) printf("%d ", arrInsertion[j]);
                        printf("\n");
                    }
                    break;
                case 3:
                    timeTaken = measureMergeSortTime(mergeSort, arrMerge, 0, size - 1);
                    printf("Metodo MergeSort: %.2f segundos\n", timeTaken);
                    if (display) {
                        printf("Arreglo ordenado por MergeSort: ");
                        for (int j = 0; j < size; j++) printf("%d ", arrMerge[j]);
                        printf("\n");
                    }
                    break;
            }
            exit(EXIT_SUCCESS);
        }
    }

    // Proceso maestro: esperar a los esclavos
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    // Liberar memoria
    free(arrBubble);
    free(arrSelection);
    free(arrInsertion);
    free(arrMerge);

    return 0;
}
