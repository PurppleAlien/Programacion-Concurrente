/*
Soria Rodriguez Juan Antonio
Matricula: 2203041232
Programa: Metodos de ordenamiento
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *A; // Apuntador a un arreglo de enteros
int *B; // Arreglo auxiliar para Merge Sort

// Prototipos de funciones
void burbuja(int n); 
void insercionDirecta(int n);
void seleccionDirecta(int n);
void mergeSort(int ini, int fin);
void merge(int ini, int mitad, int fin);  // Mezcla para merge sort
void imprimeArreglo(int n); 
void llenarArreglo(int n);
void esperarTecla(void); // Espera a que el usuario presione una tecla para regresar al menu

int main() {
    int n, opcion, mostrar;
    while (1) {
        // Menu de opciones
        printf("\nMenu de Ordenamiento\n");
        printf("1. Ordenar Arreglo por el metodo Burbuja\n");
        printf("2. Ordenar Arreglo por el metodo Insercion Directa\n");
        printf("3. Ordenar Arreglo por el metodo Seleccion Directa\n");
        printf("4. Ordenar Arreglo por el metodo MergeSort Recursivo\n");
        printf("5. Comparar el tiempo de ejecucion de todos los metodos de ordenamiento\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        // Verifica si la opcion es valida 
        if (opcion < 1 || opcion > 6) { 
            printf("Opcion no valida\n"); 
            printf("Presione cualquier tecla para regresar al menu principal...\n"); 
            getchar(); // Captura el carácter de nueva línea dejado por scanf 
            getchar(); // Espera a que el usuario presione una tecla continue; 
        }
        
        // Salir del menu si la op es 6
        if (opcion == 6) {
            break;
        }

        printf("\nIngrese el tamano del arreglo: ");
        scanf("%d", &n);

        // Asignar memoria para el arreglo 
        A = (int *)malloc(n * sizeof(int));
        B = (int *)malloc(n * sizeof(int));
        if (A == NULL || B == NULL) {
            printf("Error al asignar memoria\n");
            return 1;
        }

        // Llenar el arreglo con valores aleatorios
        llenarArreglo(n);

        printf("Quieres desplegar los elementos del arreglo??? 1 -> SI, 0 -> NO: ");
        scanf("%d", &mostrar);

        if (mostrar == 1) {
            printf("Los elementos del arreglo desordenado son:\n");
            imprimeArreglo(n);
        }

        clock_t start, end;
        double cpu_time_used;
        

        // Switch para ejecutar el algoritmo seleccionado
        switch (opcion) {
            case 1:
                start = clock();
                burbuja(n);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                if (mostrar == 1) {
                    printf("Los elementos del arreglo ordenado son:\n");
                    imprimeArreglo(n);
                }
                printf("Tiempo total del metodo Burbuja = %f segundos\n", cpu_time_used);
                break;
            case 2:
                start = clock();
                insercionDirecta(n);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                if (mostrar == 1) {
                    printf("Los elementos del arreglo ordenado son:\n");
                    imprimeArreglo(n);
                }
                printf("Tiempo total del metodo Insercion Directa = %f segundos\n", cpu_time_used);
                break;
            case 3:
                start = clock();
                seleccionDirecta(n);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                if (mostrar == 1) {
                    printf("Los elementos del arreglo ordenado son:\n");
                    imprimeArreglo(n);
                }
                printf("Tiempo total del metodo Seleccion Directa = %f segundos\n", cpu_time_used);
                break;
            case 4:
                start = clock();
                mergeSort(0, n - 1);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                if (mostrar == 1) {
                    printf("Los elementos del arreglo ordenado son:\n");
                    imprimeArreglo(n);
                }
                printf("Tiempo total del metodo MergeSort Recursivo = %f segundos\n", cpu_time_used);
                break;
            case 5:
                printf("Comparando tiempos de ejecucion...\n");

                // Método Burbuja
                llenarArreglo(n);
                start = clock();
                burbuja(n);
                end = clock();
                double tiempo_burbuja = ((double)(end - start)) / CLOCKS_PER_SEC;

                // Método Insercion Directa
                llenarArreglo(n);
                start = clock();
                insercionDirecta(n);
                end = clock();
                double tiempo_insercion = ((double)(end - start)) / CLOCKS_PER_SEC;

                // Método Selección Directa
                llenarArreglo(n);
                start = clock();
                seleccionDirecta(n);
                end = clock();
                double tiempo_seleccion = ((double)(end - start)) / CLOCKS_PER_SEC;

                // Método Merge Sort
                llenarArreglo(n);
                start = clock();
                mergeSort(0, n - 1);
                end = clock();
                double tiempo_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

                printf("Tiempo metodo Burbuja = %f segundos\n", tiempo_burbuja);
                printf("Tiempo metodo Insercion Directa = %f segundos\n", tiempo_insercion);
                printf("Tiempo metodo Seleccion Directa = %f segundos\n", tiempo_seleccion);
                printf("Tiempo metodo MergeSort Recursivo = %f segundos\n", tiempo_merge);
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }

        // Llamar a la función esperarTecla antes de liberar memoria y regresar al menú
        esperarTecla();

        // Liberar memoria
        free(A);
        free(B);
    }

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

// Algoritmo de Insercion Directa
void insercionDirecta(int n) {
    for (int i = 1; i < n; i++) {
        int aux = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > aux) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = aux;
    }
}

// Algoritmo de Seleccion Directa
void seleccionDirecta(int n) {
    for (int i = 0; i < n - 1; i++) {
        int pos_min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[pos_min]) {
                pos_min = j;
            }
        }
        int temp = A[i];
        A[i] = A[pos_min];
        A[pos_min] = temp;
    }
}

// Algoritmo Merge Sort (Ordenamiento por Mezcla)
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
        if (A[i] <= A[j]) {
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

// Función para llenar el arreglo con valores aleatorios (entre 0 y 1000) y (0 y 100,000) 
void llenarArreglo(int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1001; // Generar números aleatorios entre 0 y 1000
        //A[i] = rand() % 100001; //Generar números aleatorios entre 0 y 100,000
    }
}

// Función para esperar a que el usuario presione una tecla para regresar al menu 
void esperarTecla(void) {
    printf("Presione cualquier tecla para regresar al menu principal...\n");
    getchar(); // Captura el ENTER anterior
    getchar(); // Espera a que el usuario presione una tecla
}



