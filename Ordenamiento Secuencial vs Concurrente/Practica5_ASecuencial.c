#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipos de funciones
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void fillArray(int arr[], int n);
void displayArray(int arr[], int n);

int main() {
    int n, display;
    clock_t start, end;
    double time_used;

    // Solicitar tamaño del arreglo
    printf("Dame el tamano de los elementos del arreglo: ");
    scanf("%d", &n);

    // Solicitar si se deben mostrar los elementos
    printf("Quieres desplegar los elementos del arreglo? 1-> si, 0-> no: ");
    scanf("%d", &display);

    // Reservar memoria para el arreglo
    int *arrBubble = (int *)malloc(n * sizeof(int));
    int *arrInsertion = (int *)malloc(n * sizeof(int));
    int *arrSelection = (int *)malloc(n * sizeof(int));
    int *arrMerge = (int *)malloc(n * sizeof(int));

    // Llenar arreglos con valores aleatorios
    fillArray(arrBubble, n);
    for (int i = 0; i < n; i++) {
        arrInsertion[i] = arrBubble[i];
        arrSelection[i] = arrBubble[i];
        arrMerge[i] = arrBubble[i];
    }

    if (display) {
        printf("Elementos iniciales:\n");
        displayArray(arrBubble, n);
    }
    
    //ORDENAMIENTO SECUENCIAL
     printf("\nORDENAMIENTO SECUENCIAL\n");

    // Ordenamiento por burbuja
    start = clock();
    bubbleSort(arrBubble, n);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Metodo Burbuja: %.2f segundos\n", time_used);

    // Ordenamiento por inserción directa
    start = clock();
    insertionSort(arrInsertion, n);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Metodo Insercion Directa: %.2f segundos\n", time_used);

    // Ordenamiento por selección directa
    start = clock();
    selectionSort(arrSelection, n);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Metodo Seleccion Directa: %.2f segundos\n", time_used);

    // Ordenamiento por MergeSort
    start = clock();
    mergeSort(arrMerge, 0, n - 1);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Metodo MergeSort: %.2f segundos\n", time_used);

    // Tiempo total
    double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo total de ejecucion del programa: %.2f segundos\n", total_time);

    if (display) {
        printf("Arreglo ordenado:\n");
        displayArray(arrMerge, n);
    }

    // Liberar memoria
    free(arrBubble);
    free(arrInsertion);
    free(arrSelection);
    free(arrMerge);

    return 0;
}

// Implementación de Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Implementación de Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Implementación de Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Implementación de Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
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

// Llenar arreglo con valores aleatorios
void fillArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Mostrar arreglo
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

